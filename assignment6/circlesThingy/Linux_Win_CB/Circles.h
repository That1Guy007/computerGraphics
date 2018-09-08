#ifndef CIRCLES_H_INCLUDED
#define CIRCLES_H_INCLUDED

#include <GL/glew.h>

#include <math.h>
#include "ProgramDefines.h"

class Circles{
private:
    GLint sides;
    GLuint PolygonVao;
    GLuint ArrayBuffer;

    void LoadDataToGraphicsCard();
public:
    Circles(GLint s = 360);
    ~Circles();

    void setSides(GLint s);
    GLint getSides();

    void draw();
};
#endif // CIRCLES_H_INCLUDED
