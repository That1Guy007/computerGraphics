#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <GL/glew.h>
#endif // __APPLE__

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>

#include "GraphicsEngine.h"
#include "UI.h"

/**
\mainpage Aspect Ratio Example

\tableofcontents

\section intro Introduction

In this example, we create 9 squares of various sizes and positions, and using
a uniform variable projection matrix in the shader keep the objects looking
like squares when the screen is resized.

The graphics window will display 9 multicolored squares.  The title bar of
the window will also display the number of frames per second for the last second.

\subsection options User Options

- Escape:  Ends the program.
- M: Toggles between fill mode and line mode to draw the triangles.
- R: Resets the window size to 700 X 500.
- A: Resets the window size to 600 X 600.
- F1: Sets vertex 0 of the box to (1, 0.3, 0.21)
- F2: Sets vertex 0 of the box to (1, 0.3, 0.21)
- F5: Resets the box center to (0, 0).
- F10: Saves a screen shot of the graphics window to a png file.
- 1 - 9: Sets the current box to be altered.
- Left: Moves the box to the left.
- Right: Moves the box to the right.
- Up: Moves the box up.
- Down: Moves the box down.

\note Note that the shader programs "AspectRatioVert.glsl" and "PassThroughFrag.glsl" are expected
to be in the same folder as the executable.  Your graphics card must also be able to support
OpenGL version 3.3 to run this program.


---

\subsection copyright Copyright

\author    Don Spickler
\version   1.2
\date      1/6/2018
\copyright 2018


---

\subsection license License

GNU Public License

This software is provided as-is, without warranty of ANY KIND, either expressed or implied,
including but not limited to the implied warranties of merchant ability and/or fitness for a
particular purpose. The authors shall NOT be held liable for ANY damage to you, your computer,
or to anyone or anything else, that may result from its use, or misuse.
All trademarks and other registered names contained in this package are the property
of their respective owners.  USE OF THIS SOFTWARE INDICATES THAT YOU AGREE TO THE ABOVE CONDITIONS.

*/

/**
\file main.cpp
\brief Main driver for the program.

This is the main program driver that sets up the graphics engine and links it to
the user interface processor.

\author    Don Spickler
\version   1.2
\date      12/22/2017

*/


/**
\brief The Main function, program entry point.

\return Standard EXIT_SUCCESS return on successful run.

The main function, responsible for initializing OpenGL and setting up
the SFML interface for OpenGL.

*/

int main()
{
    //  Program setup variables.
    std::string programTitle = "Aspect Ratio Example";
    GLint MinMajor = 3;
    GLint MinMinor = 3;
    GLint WindowWidth = 700;
    GLint WindowHeight = 500;
    bool DisplayInfo = true;

    //  Other variables
    GLint major;
    GLint minor;
    sf::Clock clock;
    sf::Time time = clock.restart();
    long framecount = 0;

    // Try core context of 10.10 (too advanced) and see what card will resort to.
    // For setting up OpenGL, GLEW, and check versions.
    sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "OpenGL Setup", sf::Style::Default,
                            sf::ContextSettings(24, 8, 4, 10, 10, sf::ContextSettings::Core));

    window.setVisible(false);

#ifndef __APPLE__
    // Turn on GLEW for Windows and Linux.
    glewExperimental = true;
    if (glewInit())
    {
        std::cerr << "\nUnable to initialize GLEW ... exiting. \n";
        exit(EXIT_FAILURE);
    }
#endif // __APPLE__

    //  Get major and minor OpenGL version from graphics card.
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    //  Check card version to minimum required version.
    bool versionOK = true;
    if (major < MinMajor)
        versionOK = false;
    else if (major == MinMajor && minor < MinMinor)
        versionOK = false;

    if (!versionOK)
    {
        std::cerr << "\nGraphics card OpenGL version is " << major << "." << minor << std::endl;
        std::cerr << "Program required OpenGL version is " << MinMajor << "." << MinMinor << std::endl;
        std::cerr << "Exiting\n";
        exit(EXIT_FAILURE);
    }

    //  Output OpenGL version to the console window.
    if (DisplayInfo)
    {
        std::cout << "\n";
        std::cout << "Version  = " << glGetString(GL_VERSION) << "\n";
        std::cout << "Major    = " << major << "\n";
        std::cout << "Minor    = " << minor << "\n";
        std::cout << "Vendor   = " << glGetString(GL_VENDOR) << "\n";
        std::cout << "Renderer = " << glGetString(GL_RENDERER) << "\n";
        std::cout << "\n";
    }
    //  Close setup window and context.
    window.close();

    //  Create graphics engine.
    GraphicsEngine ge(programTitle, major, minor, WindowWidth, WindowHeight);
    UI ui(&ge);

    // Start the Game/GUI loop
    while (ge.isOpen())
    {
        // Call the display function to do the OpenGL rendering.
        //ge.display();

        // Process any events.
        ui.processEvents();

        //  Increment frame counts
        framecount++;

        //  Get Elapsed Time
        float timesec = clock.getElapsedTime().asSeconds();
        char titlebar[1000];

        //  If another second has elapsed, display the FPS and total FPS.
        if (timesec > 1.0)
        {
            float fps = framecount / timesec;
            sprintf(titlebar, "%s     FPS: %.2f", programTitle.c_str(), fps);
            ge.setTitle(titlebar);
            time = clock.restart();
            framecount = 0;
        }
    }

    return EXIT_SUCCESS;
}
