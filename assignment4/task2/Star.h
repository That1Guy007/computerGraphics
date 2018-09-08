#ifndef STAR_H_INCLUDED
#define STAR_H_INCLUDED

#include <GL/glew.h>

#include <iostream>
#include <stdlib.h>
#include <math.h>

#include "ProgramDefines.h"
#include "Shape.h"


/**
\file Star.h

\brief Header file for Star.cpp

\author    Don Spickler, Carlos Hernandez
\version   1.3.1
\date      3/2/2018

*/

/**
\class Star

\brief The star class holds position and color data for a star.  It also has
facilities for loading the data to the graphics card and invoking draw commands on the data.

*/


class Star : public Shape{

private:
    GLfloat radius;     ///< radius of the star
    GLint points;       ///< points of the star
    GLfloat centerX;    ///< center of the star X val
    GLfloat centerY;    ///<  center of the star Y val
    GLfloat color[3];   ///< color of the tips
    GLfloat centerColor[3]; ///< color of the center (white)

    GLuint StarVAO;     ///< star VAO
    GLuint StarEBO;     ///< star EBO
    GLuint ArrayBuffer; ///< array buffer object

    void LoadDataToGraphicsCard();  ///< loads data to the graphics

public:

    Star(GLfloat cx = 0, GLfloat cy = 0, GLfloat r = 1, GLint s = 8);   ///< star constructor
    ~Star();    ///< star destructor

    void setRadius(GLfloat);    ///< sets radius
    void setPoints(GLint);      ///< set points
    void setCenter(GLfloat, GLfloat);   ///< set center
    void setPointColor(GLfloat, GLfloat, GLfloat);  ///< set tips color
    void setCenterColor(GLfloat, GLfloat, GLfloat); ///< set center color

    GLfloat getRadius();    ///< grab radius
    GLint getPoints();      ///< get the # of points
    void getCenter(GLfloat*);   ///< get center

    void draw();        ///< draw object
};


#endif // STAR_H_INCLUDED
