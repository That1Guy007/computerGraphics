#ifndef AXES2D_H_INCLUDED
#define AXES2D_H_INCLUDED

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <GL/glew.h>
#endif // __APPLE__

#include <iostream>
#include <stdlib.h>

#include "ProgramDefines.h"
#include "Shape.h"

/**
\file Axes2D.h

\brief Header file for Axes2D.cpp

\author    Don Spickler, Carlos Hernandez
\version   1.1
\date      1/7/2018

*/

/**
\class Axes2D

\brief The Axes2D class is for displaying a set of 2-D axes on the screen.  It also has
facilities for loading the data to the graphics card and invoking draw commands on the data.

*/

class Axes2D : public Shape
{
private:
    GLfloat XExtent;        ///< Extent of the x-axis.
    GLfloat YExtent;        ///< Extent of the y-axis.
    GLfloat XAxisColor[3];  ///< Array holding the (r,g,b) color values for the x-axis.
    GLfloat YAxisColor[3];  ///< Array holding the (r,g,b) color values for the y-axis.

    GLuint BoxVAO;        ///< Vertex Array Object ID.
    GLuint ArrayBuffer;   ///< Vertex and Color Information Array Buffer ID.
    GLuint BoxEBO;        ///< Indices Array Object ID.

    GLint vPosition;      ///< Array Buffer position index.
    GLint vColor;         ///< Array Buffer color index.

    void LoadDataToGraphicsCard();

public:
    Axes2D(GLfloat XExt = 1, GLfloat YExt = 1);
    ~Axes2D();

    void setXExtent(GLfloat e);
    void setYExtent(GLfloat e);
    void setXAxisColor(GLfloat r, GLfloat g, GLfloat b);
    void setYAxisColor(GLfloat r, GLfloat g, GLfloat b);
    GLfloat getXExtent();
    GLfloat getYExtent();

    void draw();
};

#endif // AXES2D_H_INCLUDED
