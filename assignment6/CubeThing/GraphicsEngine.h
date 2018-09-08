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
#include <iostream>
#include <string>
#include <stdio.h>

#include "LoadShaders.h"
#include "Cube.h"
#include "ProgramDefines.h"
#include "SphericalCamera.h"
#include "YPRCamera.h"
#include "Axes.h"

/**
\file GraphicsEngine.h
\brief Header file for GraphicsEngine.cpp

\author    Don Spickler, Carlos H.
\version   1.2
\date      1/14/2018

*/

/**
\class GraphicsEngine

\brief The GraphicsEngine class is an extension of sf::RenderWindow which
handles all of the graphics rendering in the program.

*/

class GraphicsEngine : public sf::RenderWindow
{
private:
    GLenum mode;    ///< Mode, either point, line or fill.
    int sscount;    ///< Screenshot count to be appended to the screenshot filename.
    Cube box;       ///< Simple cube object.
    Axes coords;    ///< Axes Object

    bool PorS;
    bool anim1;
    bool anim2;
    bool anim3;
    bool anim4;
    bool anim5;
    bool anim6;
    bool anim7;
    bool anim8;
    bool anim9;

    GLuint ProjLoc;      ///< Location ID of the Projection matrix in the shader.
    GLuint ViewLoc;      ///< Location ID of the View matrix in the shader.
    GLuint ModelLoc;     ///< Location ID of the Model matrix in the shader.

    SphericalCamera sphcamera;  ///< Spherical Camera
    YPRCamera yprcamera;        ///< Yaw-Pitch-Roll Camera
    int CameraNumber;           ///< Camera number 1 = spherical, 2 = yaw-pitch-roll.

    glm::mat4 projection;       ///< Projection Matrix

    GLboolean drawAxes;        ///< Boolean for axes being drawn.
    GLboolean drawManyBoxes;   ///< Boolean for many boxes verses one box being drawn.
    GLboolean drawBoxes;       ///< Boolean for boxes being drawn.

    void printOpenGLErrors();
    void print_GLM_Matrix(glm::mat4 m);

public:
    GraphicsEngine(std::string title = "OpenGL Window", GLint MajorVer = 3, GLint MinorVer = 3,
                   int width = 600, int height = 600);
    ~GraphicsEngine();

    void display();
    void changeMode();
    void screenshot();
    void resize();
    void setSize(unsigned int, unsigned int);
    GLfloat* getScreenBounds();
    Cube* getBox();

    void animation(int, int, int);
    void animationP(int, int, int);

    float multi0, multi1, multi2, multi3, multi4, multi5, multi6, multi7, multi8;

    void setStartAnim(bool);

    bool getStartAnim();

    void setAnim1(bool);
    void setAnim2(bool);
    void setAnim3(bool);
    void setAnim4(bool);
    void setAnim5(bool);
    void setAnim6(bool);
    void setAnim7(bool);
    void setAnim8(bool);
    void setAnim9(bool);


    bool getAnim1();
    bool getAnim2();
    bool getAnim3();
    bool getAnim4();
    bool getAnim5();
    bool getAnim6();
    bool getAnim7();
    bool getAnim8();
    bool getAnim9();




    void setDrawManyBoxes(GLboolean b);
    void setDrawBoxes(GLboolean b);
    void setDrawAxes(GLboolean b);

    GLboolean isSphericalCameraOn();
    void setSphericalCameraOn();
    GLboolean isYPRCameraOn();
    void setYPRCameraOn();

    SphericalCamera* getSphericalCamera();
    YPRCamera* getYPRCamera();
};

#endif // GRAPHICSENGINE_H_INCLUDED
