#include "Circles.h"
///author    Don Spickler,Carlos Hernandez
//version   1.2
//date      1/14/2018
Circles::Circles(GLint s){
    sides = s;

    glGenVertexArrays(1, &PolygonVao);
    glGenBuffers(1, &ArrayBuffer);

    LoadDataToGraphicsCard();
}

Circles::~Circles(){
    glBindVertexArray(PolygonVao);
    glDeleteBuffers(1, &ArrayBuffer);
}

void Circles::LoadDataToGraphicsCard(){
    GLuint vPosition = 0;
    GLfloat verticies[2 * sides];

    for(int s = 0; s < sides; s++){
        verticies[2*s] = cos((2*PI) * s/sides);
        verticies[2 * s + 1] = sin((2* PI) * s / sides);
    }

    glBindVertexArray(PolygonVao);
    glBindBuffer(GL_ARRAY_BUFFER, ArrayBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(vPosition);
}

void Circles::setSides(GLint s){
    sides = s;
    LoadDataToGraphicsCard();
}

GLint Circles::getSides(){
    return sides;
}

void Circles::draw(){
    glBindVertexArray(PolygonVao);
    glDrawArrays(GL_LINE_LOOP, 0, sides);
}
