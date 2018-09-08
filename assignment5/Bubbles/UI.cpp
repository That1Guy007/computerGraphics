#include "UI.h"

/**
\file UI.cpp
\brief User interface processor for the program.

\author    Don Spickler,Carlos Hernandez
\version   1.2
\date      1/7/2018

*/

/**
\brief Constructor

\param graph --- Pointer to the GraphicsEngine that this interface processor is attached.

Simply stores the pointer of the GraphicsEngine.

*/

UI::UI(GraphicsEngine* graph)
{
    ge = graph;
    boxnum = 0;
    mouseDown = false;
}

/**
\brief Destructor

No implementation needed at this point.

*/

UI::~UI() {}

/**
\brief The method handles the SFML event processing.

This method processes all events in the current SFML event queue and calls
the corresponding processing method.

*/

void UI::processEvents()
{
    // Process user events
    sf::Event event;
    while (ge->pollEvent(event))
    {
        // Close Window or Escape Key Pressed: exit
        if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            ge->close();

        // Key is pressed.
        if (event.type == sf::Event::KeyPressed)
            keyPressed(event.key);

        // Window is resized.
        if (event.type == sf::Event::Resized)
            ge->resize();
    }

    keyboardStateProcessing();
}



/**
\brief The function handles the keyboard input from the user.

\param keyevent --- The SFML key event.

\remark

- M: Toggles between fill mode and line mode to draw the triangles.
- R: Resets the window size to 700 X 500.
- A: Resets the window size to 600 X 600.
- F1: Sets vertex 0 of the box to (1, 0.3, 0.21)
- F2: Sets vertex 0 of the box to (1, 0.3, 0.21)
- F5: Resets the box center to (0, 0).
- F10: Saves a screen shot of the graphics window to a png file.
- 1 - 9: Sets the current box to be altered.

*/

void UI::keyPressed(sf::Event::KeyEvent keyevent)
{
    switch (keyevent.code)
    {
    // Sets the current box to be altered.
    case sf::Keyboard::Num1:
    case sf::Keyboard::Num2:
    case sf::Keyboard::Num3:
    case sf::Keyboard::Num4:
    case sf::Keyboard::Num5:
    case sf::Keyboard::Num6:
    case sf::Keyboard::Num7:
    case sf::Keyboard::Num8:
    case sf::Keyboard::Num9:
        boxnum = keyevent.code - sf::Keyboard::Num0 - 1;
        break;

    // F1 Sets vertex 0 of the box to (1, 0.3, 0.21)
    case sf::Keyboard::F1:
        //ge->getBox(boxnum)->setVertexColor(0, 1, 0.3, 0.21);
        break;

    // F2 Sets vertex 0 of the box to (1, 0.3, 0.21)
    case sf::Keyboard::F2:
        //ge->getBox(boxnum)->setVertexColor(1, 1, 0.3, 0.21);
        break;

    // F5 Resets the box center to (0, 0)
    case sf::Keyboard::F5:
        //ge->getBox(boxnum)->setCenter(0, 0);
        break;

    // F10 takes a screenshot saves as JPG.
    case sf::Keyboard::F10:
        ge->screenshot();
        break;

    // If the M key is pressed toggle the display mode between Fill and Line.
    case sf::Keyboard::M:
        ge->changeMode();
        break;

    // Resets the window to (700, 500)
    case sf::Keyboard::R:
        ge->setSize(700, 500);
        break;

    // Sets the window to (600, 600)
    case sf::Keyboard::A:
        ge->setSize(600, 600);
        break;

    default:
        break;
    }
}

/**
\brief The method processes the keyboard state.

\remark

- Left: Moves the box to the left.
- Right: Moves the box to the right.
- Up: Moves the box up.
- Down: Moves the box down.

*/

void UI::keyboardStateProcessing()
{
    GLfloat BoxCenter[2];

    // Change the box position.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        //ge->getBox(boxnum)->getCenter(BoxCenter);
        //ge->getBox(boxnum)->setCenter(BoxCenter[0]-0.01, BoxCenter[1]);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        //ge->getBox(boxnum)->getCenter(BoxCenter);
        //ge->getBox(boxnum)->setCenter(BoxCenter[0]+0.01, BoxCenter[1]);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        //ge->getBox(boxnum)->getCenter(BoxCenter);
        //ge->getBox(boxnum)->setCenter(BoxCenter[0], BoxCenter[1]+0.01);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        //ge->getBox(boxnum)->getCenter(BoxCenter);
        //ge->getBox(boxnum)->setCenter(BoxCenter[0], BoxCenter[1]-0.01);
    }
}
