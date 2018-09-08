#ifndef STAR_H_INCLUDED
#define STAR_H_INCLUDED

#include <GL/glew.h>

#include <iostream>
#include <stdlib.h>
#include <math.h>

#include "ProgramDefines.h"
#include "Shape.h"


/*
  Author: Don Spickler, Carlos Hernandez
  Date: 3/02/2018
  version: 1.2.1
*/


class Star : public Shape{

private:
    GLfloat radius;
    GLint points;
    GLfloat centerX;
    GLfloat centerY;
    GLfloat color[3];
    GLfloat centerColor[3];

    GLuint StarVAO;
    GLuint StarEBO;
    GLuint ArrayBuffer;

    void LoadDataToGraphicsCard();

public:

    Star(GLfloat cx = 0, GLfloat cy = 0, GLfloat r = 1, GLint s = 8);
    ~Star();

    void setRadius(GLfloat);
    void setPoints(GLint);
    void setCenter(GLfloat, GLfloat);
    void setPointColor(GLfloat, GLfloat, GLfloat);
    void setCenterColor(GLfloat, GLfloat, GLfloat);

    GLfloat getRadius();
    GLint getPoints();
    void getCenter(GLfloat*);

    void draw();
};


#endif // STAR_H_INCLUDED
