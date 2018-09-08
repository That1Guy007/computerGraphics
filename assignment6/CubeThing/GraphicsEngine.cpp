#include "GraphicsEngine.h"

/**
\file GraphicsEngine.cpp
\brief Main graphics driver for the program.

This class extends sf::RenderWindow.

\author    Don Spickler, Carlos
\version   1.2
\date      1/14/2018

*/

/**
\brief Constructor

\param title --- Title to be placed in the titlebar of the graphics window.
\param MajorVer --- The OpenGL major version that is requested.
\param MinorVer --- The OpenGL minor version that is requested.
\param width --- The width (in pixels) of the graphics window.
\param height --- The height (in pixels) of the graphics window.

Creates rendering window, loads the shaders, and sets some initial data settings.

*/

GraphicsEngine::GraphicsEngine(std::string title, GLint MajorVer, GLint MinorVer, int width, int height) :
    sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Default,
                     sf::ContextSettings(24, 8, 4, MajorVer, MinorVer, sf::ContextSettings::Core))
{
    //  Load the shaders
    GLuint program = LoadShadersFromFile("VertexShaderBasic3D.glsl", "PassThroughFrag.glsl");

    if (!program)
    {
        std::cerr << "Could not load Shader programs." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Turn on the shader & get location of transformation matrix.
    glUseProgram(program);
    ProjLoc = glGetUniformLocation(program, "Proj");
    ViewLoc = glGetUniformLocation(program, "View");
    ModelLoc = glGetUniformLocation(program, "Model");

    PorS = false;
    anim1 = false;
    anim2 = false;
    anim3 = false;
    anim4 = false;
    anim5 = false;
    anim6 = false;
    anim7 = false;
    anim8 = false;
    anim9 = false;

    multi0 = 0;
    multi1 = 0;
    multi2 = 0;
    multi3 = 0;
    multi4 = 0;
    multi5 = 0;
    multi6 = 0;
    multi7 = 0;
    multi8 = 0;

    // Initialize some data.
    mode = GL_FILL;
    sscount = 1;
    CameraNumber = 1;
    drawAxes = GL_TRUE;
    drawManyBoxes = GL_TRUE;
    drawBoxes = GL_TRUE;

    // Set position of spherical camera
    sphcamera.setPosition(30, 30, 20);

    // Enable depth and cull face.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    if (SetVS)
    {
        setVerticalSyncEnabled(true);
        setFramerateLimit(60);
    }
    else
    {
        setVerticalSyncEnabled(false);
        setFramerateLimit(0);
    }

    // Make it the active window for OpenGL calls, resize to set projection matrix.
    setActive();
    glClearColor(0, 0, 0, 1);

    resize();
}

/**
\brief Destructor

Currently empty, no allocated memory to clear.

*/

GraphicsEngine::~GraphicsEngine() {}

/**
\brief The function responsible for drawing to the OpenGL frame buffer.

This function clears the screen and calls the draw functions of the box and circle.

*/

void GraphicsEngine::display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set view matrix via current camera.
    glm::mat4 view(1.0);
    if (CameraNumber == 1)
        view = sphcamera.lookAt();
    else if (CameraNumber == 2)
        view = yprcamera.lookAt();

    // Load view matrix to shader.
    glUniformMatrix4fv(ViewLoc, 1, GL_FALSE, glm::value_ptr(view));

    // Set axes scaling.
    glm::mat4 axesscale = glm::scale(glm::mat4(1.0), glm::vec3(10, 10, 10));

    // Load matrix product to shader.
    glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(axesscale));

    if (drawAxes)
        coords.draw();

    if (drawBoxes)
    {
        if (drawManyBoxes)
        {
            for (int i = -10; i <= 10; i+=4)
                for (int j = -10; j <= 10; j+=4)
                    for (int k = -10; k <= 10; k+=4)
                    {

                        if(PorS)
                        {
                            animation(i,j,k);

                        }

                        else
                        {
                            animationP(i,j,k);
                        }
                    }
        }
        else
        {
            // Load model matrix to shader.
            glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0)));
            box.draw();
        }
    }

    sf::RenderWindow::display();
    printOpenGLErrors();
}

void GraphicsEngine::animation(int i, int j, int k)
{
    if(anim1)
    {
        glm::mat4 model = glm::rotate(glm::translate(glm::mat4(1.0), glm::vec3(i, j, k)), multi0*degf, glm::vec3(0, 0, 1));
        glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));
        box.draw();
        multi0 += 0.005;
    }

    else if(anim2)
    {
        glm::mat4 model = glm::translate(glm::rotate(glm::mat4(1.0), multi1*degf, glm::vec3(0,0,1)), glm::vec3(i,j,k));
        glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));
        box.draw();
        multi1 += 0.005;
    }
    else if(anim3)
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(i,j,k));
        model = glm::scale(model, glm::vec3(fabs(3*cos(multi2*degf)),fabs(3*cos(multi2*degf)),fabs(3*cos(multi2*degf))));
        glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));
        box.draw();
        multi2 += 0.005;
    }

    else if(anim4)
    {
        glm::mat4 model = glm::scale(glm::mat4(1.0), glm::vec3(fabs(cos(multi3*degf)), fabs(cos(multi3*degf)), fabs(cos(multi3*degf))));
        model = glm::translate(model, glm::vec3(i,j,k));
        glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));
        box.draw();
        multi3 += 0.005;
    }

    else if(anim5)
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(i*cos(multi4*degf),j,k));
        glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));
        box.draw();
        multi4 += 0.005;
    }

    else if(anim6)
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(i*cos(multi5*degf), j*cos(multi5*degf), k*cos(multi5*degf)));
        glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));
        box.draw();
        multi5 += 0.005;
    }

    else if(anim7)
    {
        glm::mat4 model = glm::translate(glm::rotate(glm::mat4(1.0), multi6*degf, glm::vec3(0,0,-1)), glm::vec3(i,j,k));
        model = glm::rotate(model, multi6*degf, glm::vec3(0,0,1));
        glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));
        box.draw();
        multi6 += 0.005;
    }
    else if(anim8)
    {
        glm::mat4 model = glm::translate(glm::rotate(glm::mat4(1.0), multi7*degf, glm::vec3(-1,-1,-1)), glm::vec3(i,j,k));
        model = glm::rotate(model, multi7*degf, glm::vec3(1,1,1));
        glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));
        box.draw();
        multi7 += 0.005;
    }
    else if(anim9)
    {
        glm::mat4 model = glm::translate(glm::rotate(glm::mat4(1.0), multi8*degf, glm::vec3(i, j, k)), glm::vec3(i,j,k));
        glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));
        box.draw();
        multi8 += 0.005;
    }

}

void GraphicsEngine::animationP(int i, int j, int k)
{
    if(anim1)
    {
        glm::mat4 model = glm::rotate(glm::translate(glm::mat4(1.0), glm::vec3(i, j, k)), multi0*degf, glm::vec3(0, 0, 1));
        glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));
        box.draw();

    }

    else if(anim2)
    {
        glm::mat4 model = glm::translate(glm::rotate(glm::mat4(1.0), multi1*degf, glm::vec3(0,0,1)), glm::vec3(i,j,k));
        glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));
        box.draw();
    }
    else if(anim3)
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(i,j,k));
        model = glm::scale(model, glm::vec3(fabs(3*cos(multi2*degf)),fabs(3*cos(multi2*degf)),fabs(3*cos(multi2*degf))));
        glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));
        box.draw();

    }

    else if(anim4)
    {
        glm::mat4 model = glm::scale(glm::mat4(1.0), glm::vec3(fabs(cos(multi3*degf)), fabs(cos(multi3*degf)), fabs(cos(multi3*degf))));
        model = glm::translate(model, glm::vec3(i,j,k));
        glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));
        box.draw();
    }

    else if(anim5)
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(i*cos(multi4*degf),j,k));
        glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));
        box.draw();
    }

    else if(anim6)
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(i*cos(multi5*degf), j*cos(multi5*degf), k*cos(multi5*degf)));
        glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));
        box.draw();

    }

    else if(anim7)
    {
        glm::mat4 model = glm::translate(glm::rotate(glm::mat4(1.0), multi6*degf, glm::vec3(0,0,-1)), glm::vec3(i,j,k));
        model = glm::rotate(model, multi6*degf, glm::vec3(0,0,1));
        glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));
        box.draw();
    }
    else if(anim8)
    {
        glm::mat4 model = glm::translate(glm::rotate(glm::mat4(1.0), multi7*degf, glm::vec3(-1,-1,-1)), glm::vec3(i,j,k));
        model = glm::rotate(model, multi7*degf, glm::vec3(1,1,1));
        glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));
        box.draw();
    }
    else if(anim9)
    {
        glm::mat4 model = glm::translate(glm::rotate(glm::mat4(1.0), multi8*degf, glm::vec3(i, j, k)), glm::vec3(i,j,k));
        glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));
        box.draw();
    }

}

/**
\brief Changes the fill and line mode being used.

*/

void GraphicsEngine::changeMode()
{
    if (mode == GL_FILL)
        mode = GL_LINE;
    else
        mode = GL_FILL;

    glPolygonMode(GL_FRONT_AND_BACK, mode);
}

/**
\brief Saves a screenshot of the current display to a file, ScreenShot###.png.

*/

void GraphicsEngine::screenshot()
{
    char ssfilename[100];
    sprintf(ssfilename, "ScreenShot%d.png", sscount);
    sf::Vector2u windowSize = getSize();
    sf::Texture texture;
    texture.create(windowSize.x, windowSize.y);
    texture.update(*this);
    sf::Image img = texture.copyToImage();
    img.saveToFile(ssfilename);
    sscount++;
}

/**
\brief Handles the resizing events of the window.

Sets the viewport to the entire screen and recalculates the projection matrix.
*/

void GraphicsEngine::resize()
{
    glViewport(0, 0, getSize().x, getSize().y);
    projection = glm::perspective(50.0f*degf, (float)getSize().x/getSize().y, 0.01f, 500.0f);

    // Load projection matrix to shader.
    glUniformMatrix4fv(ProjLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

/**
\brief Sets the size of the rendering window.

\param width --- the width in pixels of the new size.

\param height --- the height in pixels of the new size.

*/

void GraphicsEngine::setSize(unsigned int width, unsigned int height)
{
    sf::RenderWindow::setSize(sf::Vector2u(width, height));
}

/**
\brief Returns a pointer to the box object.

*/

Cube* GraphicsEngine::getBox()
{
    return &box;
}

/**
\brief Returns a pointer to the spherical camera.

*/

SphericalCamera* GraphicsEngine::getSphericalCamera()
{
    return &sphcamera;
}

/**
\brief Returns a pointer to the yaw-pitch-roll camera.

*/

YPRCamera* GraphicsEngine::getYPRCamera()
{
    return &yprcamera;
}

/**
\brief Prints all OpenGL errors to stderr.

*/

void GraphicsEngine::printOpenGLErrors()
{
    GLenum errCode;
    const GLubyte *errString;

    while ((errCode = glGetError()) != GL_NO_ERROR)
    {
        errString = gluErrorString(errCode);
        fprintf(stderr, "OpenGL Error: %s\n", errString);
    }
}

/**
\brief Prints the glm matrix to the console window.  Remember that glm
matrices are column major.

\param m --- the glm matrix to be displayed.

*/

void GraphicsEngine::print_GLM_Matrix(glm::mat4 m)
{
    for (int r = 0; r < 4; r++)
    {
        for (int c = 0; c < 4; c++)
            printf("%7.2f", m[c][r]);

        std::cout << std::endl;
    }
    std::cout << std::endl;
}

/**
\brief Sets the boolean to draw a grid of boxes if true and a single box if false.

\param b --- Draws a grid of boxes if true and a single box if false.

*/

void GraphicsEngine::setDrawManyBoxes(GLboolean b)
{
    drawManyBoxes = b;
}

/**
\brief Sets the boolean to draw any boxes or not.

\param b --- Draws boxes if true and not if false.

*/

void GraphicsEngine::setDrawBoxes(GLboolean b)
{
    drawBoxes = b;
}

/**
\brief Returns true if the spherical camera is currently in use.

\return True if the spherical camera is currently in use and false otherwise.

*/

GLboolean GraphicsEngine::isSphericalCameraOn()
{
    return CameraNumber == 1;
}

/**
\brief Turns the spherical camera on.

*/

void GraphicsEngine::setSphericalCameraOn()
{
    CameraNumber = 1;
}

/**
\brief Returns true if the yaw-pitch-roll camera is currently in use.

\return True if the yaw-pitch-roll camera is currently in use and false otherwise.

*/

GLboolean GraphicsEngine::isYPRCameraOn()
{
    return CameraNumber == 2;
}

/**
\brief Turns the YPR camera on.

*/

void GraphicsEngine::setYPRCameraOn()
{
    CameraNumber = 2;
}

/**
\brief Sets the boolean to draw the axes or not.

\param b --- Draws the axes if true and not if false.

*/

void GraphicsEngine::setDrawAxes(GLboolean b)
{
    drawAxes = b;
}

void GraphicsEngine::setStartAnim(bool s)
{
    PorS = s;
}
bool GraphicsEngine::getStartAnim()
{
    return PorS;
}
void GraphicsEngine::setAnim1(bool a)
{
    anim1 = a;
}
bool GraphicsEngine::getAnim1()
{
    return anim1;
}
void GraphicsEngine::setAnim2(bool a)
{
    anim2 = a;
}
bool GraphicsEngine::getAnim2()
{
    return anim2;
}
void GraphicsEngine::setAnim3(bool a)
{
    anim3 = a;
}
bool GraphicsEngine::getAnim3()
{
    return anim3;
}
void GraphicsEngine::setAnim4(bool a)
{
    anim4 = a;
}
bool GraphicsEngine::getAnim4()
{
    return anim4;
}
void GraphicsEngine::setAnim5(bool a)
{
    anim5 = a;
}
bool GraphicsEngine::getAnim5()
{
    return anim5;
}
void GraphicsEngine::setAnim6(bool a)
{
    anim6 = a;
}
bool GraphicsEngine::getAnim6()
{
    return anim6;
}
void GraphicsEngine::setAnim7(bool a)
{
    anim7 = a;
}
bool GraphicsEngine::getAnim7()
{
    return anim7;
}
void GraphicsEngine::setAnim8(bool a)
{
    anim8 = a;
}
bool GraphicsEngine::getAnim8()
{
    return anim8;
}
void GraphicsEngine::setAnim9(bool a)
{
    anim9 = a;
}
bool GraphicsEngine::getAnim9()
{
    return anim9;
}

