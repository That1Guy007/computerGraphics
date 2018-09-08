#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED

#include <GL/glew.h>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <stdio.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include "ProgramDefines.h"

/**
\file Cube.h

\brief Header file for Cube.cpp

\author    Don Spickler
\version   1.2
\date      1/14/2018

*/

/**
\class Cube

\brief The cube class draws a cube of side lengths 1 centered at the origin.

*/

class Cube
{
private:
    glm::vec4 Color;         ///< Solid color of the box, if the mode is selected.
    glm::vec4 BoarderColor;  ///< Color of the border.

    GLuint vboptr;  ///< ID for faces VBO.
    GLuint eboptr;  ///< ID for faces index array.
    GLuint bufptr;  ///< ID for faces array buffer.

    GLuint vboptrborder;  ///< ID for faces VBO.
    GLuint eboptrborder;  ///< ID for faces index array.
    GLuint bufptrborder;  ///< ID for faces array buffer.

    GLboolean drawFaces;    ///< Boolean to draw the faces.
    GLboolean drawBorder;   ///< Boolean to draw the border.
    GLboolean isColorCube;  ///< Boolean to draw the multicolor cube or solid color cube.

    void LoadDataToGraphicsCard();

public:
    Cube();
    ~Cube();

    void setDrawBorder(GLboolean d);
    void setDrawFaces(GLboolean d);
    void setColorCube(GLboolean d);

    void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1);
    void setBorderColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1);

    void draw();
};

#endif // CUBE_H_INCLUDED
