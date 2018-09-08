#include <iostream>
//include file for glew.h for linux
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <string>

#include "graphicsEngine.h"

//using namespace std;
   /*
    *   Author:     Carlos Hernandez
    *   Version:    1.1
    *   Date:       2/8/2018
    *
    */

void keyPressed(int key, graphicsEngine &ge){
    switch (key)
    {
    // If the M key is pressed toggle the display mode between Fill and Line.
    case sf::Keyboard::M:
        ge.changeMode();
        break;

    // F10 takes a screnshot.
    case sf::Keyboard::F10:
        ge.screenshot();
        break;

    case sf::Keyboard::R:
        ge.setSize(600, 600);
        break;

    default:
        break;
    }
}

int main()
{
    std::string windowTitle = "Square"; //Can be used to set the title of our window....Optional

    //major.minor version of software. OPEN GL
    GLuint minor = 3;
    GLuint major = 3;

    //optional window settings
    GLint winWidth = 600;
    GLint winHeight = 600;
    //bool displayInfo = true;

    //FPS counter variables
    char fpsTitle[1000];
    long frameCount = 0;
    long totalFrameCount = 0;

    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), windowTitle, sf::Style::Default,
                sf::ContextSettings(24, 8, 4, minor, major, sf::ContextSettings::Core));

    //Set the window to be visible
    window.setVisible(false);

    //turn on glew for windows and linux
    glewExperimental = true;
    if (glewInit()){
        std::cerr<<"\nExiting due to uninitialized GLEW\n";
        exit(1);
    }

    //create graphics engine
    graphicsEngine ge(windowTitle, major, minor, winWidth, winHeight);

    //set SFML clocks for FPS calculations
    sf::Clock clock;
    sf::Clock totalClock;
    sf::Time time = clock.restart();
    totalClock.restart();

    //the beggining of the GUI loop
    while(ge.isOpen()){
        //display function will do the openGL rendering
        ge.display();

        //event  handler
        sf::Event event;
        while(ge.pollEvent(event)){
            //close window ot escape key is pressed
            if (event.type == sf::Event::Closed ||
                    (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)){
                ge.close();
            }
            // Key is pressed.
            if (event.type == sf::Event::KeyPressed){
                keyPressed(event.key.code, ge);
            }
            // Window is resized.
            if (event.type == sf::Event::Resized){
                ge.resize();
            }
        }

        //inc frame count
        frameCount++;
        totalFrameCount++;

        //time elapsed for fps
        float timeSec = clock.getElapsedTime().asSeconds();
//        float totalTimeSecs = totalClock.getElapsedTime().asSeconds();

        if(timeSec > 1.0){
            float fps = frameCount/timeSec;
            //float totalFPS = totalFrameCount/totalTimeSecs;
            //std::cout<< "FPS: " << fps<< "\t\t" << "total FPS: "<< totalFPS << std::endl;
            sprintf(fpsTitle, "%s%s%f", windowTitle.c_str()," - ", fps );
            ge.setTitle(fpsTitle);
            time = clock.restart();
            frameCount = 0;
        }
    }
    //std::cout << "Hello world!" << std::endl;
    return EXIT_SUCCESS;
}
