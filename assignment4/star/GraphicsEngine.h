#ifndef GRAPHICSENGINE_H_INCLUDED
#define GRAPHICSENGINE_H_INCLUDED

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/glew.h>
#endif // __APPLE__

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <stdio.h>

#include "LoadShaders.h"
#include "Box.h"
#include "Star.h"
#include "Axes2D.h"
#include "ProgramDefines.h"

/**
\file GraphicsEngine.h
\brief Header file for GraphicsEngine.cpp

\author    Don Spickler
\version   1.3
\date      1/6/2018

*/

/**
\class GraphicsEngine

\brief The GraphicsEngine class is an extension of sf::RenderWindow which
handles all of the graphics rendering in the program.

*/

class GraphicsEngine : public sf::RenderWindow
{
private:
    int numBoxes;    ///< Number of boxes to draw on the screen.
    GLenum mode;     ///< Mode, either point, line or fill.
    int sscount;     ///< Screenshot count to be appended to the screenshot filename.
    Box* box;        ///< Array of box objects.
    Axes2D axes;
    Star star;

    GLuint projLoc;            ///< Location of the projection matrix in the shader program.
    GLfloat ScreenBounds[4];   ///< Bounds of the screen.
    GLuint program;            ///< Shader program ID

    std::vector<Shape*> world;  ///< Vector holding a list of all the objects in the scene.

public:
    GraphicsEngine(std::string title = "OpenGL Window", GLint MajorVer = 3, GLint MinorVer = 3,
                   int width = 600, int height = 600);
    ~GraphicsEngine();

    void display();
    void changeMode();
    void screenshot();
    void resize();
    void setSize(unsigned int, unsigned int);
    Box* getBox(int i);
    void initWorld();
    void printOpenGLErrors();
    void setProjectionMatrix();
    void print_GLM_Matrix(glm::mat4 m);
    GLfloat* getScreenBounds();
};

#endif // GRAPHICSENGINE_H_INCLUDED
