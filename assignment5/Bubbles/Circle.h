#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif // __APPLE__

#include <iostream>
#include <math.h>
#include <cstdlib>

#include "ProgramDefines.h"
#include "Shape.h"

/**
\file Polygon.h

\brief Header file for Polygon.cpp

\author    Don Spickler, Carlos Hernandez
\version   1.2
\date      1/4/2018

*/

/**
\class Polygon

\brief The Polygon class holds position and color data for a single colored polygon.  It
also has facilities for loading the data to the graphics card and invoking draw commands
on the data.

*/

class Circle
{
private:
    GLfloat radius;        ///< Radius of the polygon.
    GLint sides;           ///< The number of sides of the polygon.
    GLfloat centerX, centerY; ///< centerX and Y
    GLfloat center[2];      ///< Y coordinate of the center of the polygon.
    GLfloat color[4];      ///< (r, g, b) values for the color, in that order.
    GLfloat vel[2];
    float startsec;         ///start time in seconds
    GLfloat startPOS[2];    ///< start position

    GLuint CircleVAO;     ///< Vertex Array Object ID.
    GLuint ArrayBuffer;    ///< Vertex and Color Information Array Buffer ID.
    GLuint CircleEBO;     ///< Indices Array Object ID.

    GLint vPosition;       ///< Array Buffer position index.
    GLint vColor;          ///< Array Buffer color index.


public:
    Circle();               ///<circ constructor
    ~Circle();              ///<circ destructor

    void setRadius(GLfloat r); ///<set the radius
    void setColor(GLfloat r, GLfloat g,GLfloat b, GLfloat a = 0);  ///<set Color ???
    GLfloat getRadius();    ///<grabs the radius
    void getCenter(GLfloat* c);     ///<grabs center
    void getColor(GLfloat* c);  ///<grabs color
    void UpdatePosition(GLfloat bounds[], float sec);   ///< updates position

    void draw(); ///< draw circ
};

#endif // POLYGON_H_INCLUDED
