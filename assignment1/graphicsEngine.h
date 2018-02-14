#ifndef GRAPHICSENGINE_H_INCLUDED
#define GRAPHICSENGINE_H_INCLUDED

#include <GL/glew.h>


#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>

#include "loadShaders.h"

#define BUFFER_OFFSET(x) ((const void*) (x))
#define PI 3.14159265


using namespace std;

struct vertexInfo{
    //[r, g, b, a] red, green, blue, and instesity
    GLfloat color[3];
    //coordinates for vertex positions
    GLfloat position[4];
};

/*
graphics engine class inherits from the sf::render window.
This will handle all of the graphics rendering
*/
class graphicsEngine: public sf::RenderWindow {

    private:
        //unsigned int for number of verticies
        GLsizei numVerticies;
        //mode for full fill or outline
        GLenum mode;
        //screen shot count
        int ssCount;
        //Vertex position for shader
        GLint vPos;
        //vertex color for shader
        GLint vColor;
        //Vertex Array Object
        //This will hold buffer "locations"
        GLuint VAO;
        //Buffer of addresses
        GLuint buffer;

        GLfloat outerTipX;
        GLfloat outerTipY;
        GLfloat innerTipX;
        GLfloat innerTipY;
        GLfloat middleTipX;
        GLfloat middleTipY;

    public:
        graphicsEngine(std::string title = "OpenGL Window", GLint majorVer = 3, GLint minorVer = 3, int width = 800, int height = 600);
        //destructor
        ~graphicsEngine();

        void init();
        void display();
        void changeMode();
        void screenshot();
        void resize();
        float Xfunc(int, int);
        float Yfunc(int, int);
        void setSize(unsigned int, unsigned int);

};
#endif //for graphicsEngine_H_INCLUDED
