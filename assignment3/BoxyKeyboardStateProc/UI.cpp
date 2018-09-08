#include "UI.h"

/**
\file UI.cpp
\brief User interface processor for the program.

\author    Don Spickler, Carlos Hernandez
\version   1.2.1
\date      2/19/2018

*/

/**
\brief Constructor

\param graph --- Pointer to the GraphicsEngine that this interface processor is attached.

Simply stores the pointer of the GraphicsEngine.

*/

UI::UI(GraphicsEngine* graph)
{
    ge = graph;
}


/**
\brief Destructor

No implementation needed at this point.

*/

UI::~UI() {}

/**
\brief The method handles the SFML event processing and calls the keyboard state processor
method.

This method processes all events in the current SFML event queue and calls the
corresponding processing method.  At the end it calls the keyboard state processor
method, outside the event loop.

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

    // Process the state of the keyboard outside of event firing,
    keyboardStateProcessing();

}

/**
\brief The function handles the keyboard input events from the user.

\param keyevent --- The SFML key code for the key pressed.

\remark

If no modifier keys are pressed:

- M: Toggles between fill mode and line mode to draw the triangles.
- R: Resets the window size to 700 X 500.
- A: Resets the window size to 600 X 600.
- F10: Saves a screen shot of the graphics window to a png file.

If the control key is down:

- R: Resets the box size.

If the alt key is down:

- B: turns the whole box blue
- G: turns the whole box green
- W: turns the whole box white
- M: resets the box to its original spectrum, (red, green, blue, white)

*/

void UI::keyPressed(sf::Event::KeyEvent keyevent)
{
    int key = keyevent.code;
    bool altdown = keyevent.alt;
    bool ctrldown = keyevent.control;
    bool shiftdown = keyevent.shift;

    if (ctrldown)
    {
        // Reset the box size.
        if (key == sf::Keyboard::R)
        {
            ge->getBox()->setWidth(1);
            ge->getBox()->setHeight(1);
        }
    }
    else if (altdown)
    {
       /* // Reset the window position.
        if (key == sf::Keyboard::R)
            ge->setPosition(sf::Vector2i(20, 20)); */
        if(key == sf::Keyboard::B){
            //change box to solid blue
            ge->getBox()->setVertexColor(0, 0, 0, 1);
            ge->getBox()->setVertexColor(1, 0, 0, 1);
            ge->getBox()->setVertexColor(2, 0, 0, 1);
            ge->getBox()->setVertexColor(3, 0, 0, 1);
        }
        if(key == sf::Keyboard::G){
            //change box to solid green
            ge->getBox()->setVertexColor(0, 0, 1, 0);
            ge->getBox()->setVertexColor(1, 0, 1, 0);
            ge->getBox()->setVertexColor(2, 0, 1, 0);
            ge->getBox()->setVertexColor(3, 0, 1, 0);
        }
        if(key == sf::Keyboard::W){
            //change box to solid white
            ge->getBox()->setVertexColor(0, 1, 1, 1);
            ge->getBox()->setVertexColor(1, 1, 1, 1);
            ge->getBox()->setVertexColor(2, 1, 1, 1);
            ge->getBox()->setVertexColor(3, 1, 1, 1);
        }
        if(key == sf::Keyboard::M){
            //change box to solid blue
            ge->getBox()->setVertexColor(0, 1, 0, 0);
            ge->getBox()->setVertexColor(1, 0, 1, 0);
            ge->getBox()->setVertexColor(2, 0, 0, 1);
            ge->getBox()->setVertexColor(3, 1, 1, 1);
        }
    }
    else
    {
        switch (key)
        {
        // F10 takes a screenshot.
        case sf::Keyboard::F10:
            ge->screenshot();
            break;

        // If the M key is pressed toggle the display mode between Fill and Line.
        case sf::Keyboard::M:
            ge->changeMode();
            break;

        // Resets the screen size to 700 X 500.
        case sf::Keyboard::R:
            ge->setSize(700, 500);
            break;

        // Sets the screen size to 600 X 600.
        case sf::Keyboard::A:
            ge->setSize(600, 600);
            break;

        default:
            break;
        }
    }
}

/**
\brief The method processes the keyboard state.

\remark

If no modifier keys are pressed:

- Left: Moves the box to the left.
- Right: Moves the box to the right.
- Up: Moves the box up.
- Down: Moves the box down.

If the control key is down:

- Left: Decreases the width of the box.
- Right: Increases the width of the box.
- Up: Decreases the height of the box.
- Down: Increases the height of the box.

If the alt key is down:

- Left: Decreases the width and height of the box.
- Right: Increases the width and height of the box.

If the shift key is down:

- Left: Sets vertex 0 to a random color.
- Right: Sets vertex 1 to a random color.
- Up: Sets vertex 2 to a random color.
- Down: Sets vertex 3 to a random color.

*/

void UI::keyboardStateProcessing()
{
    GLfloat BoxCenter[2];
    float w, h;
    sf::Vector2i wp;
    sf::Vector2u ws;

    bool altdown = sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt);
    bool ctrldown = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);
    bool shiftdown = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);

    if (ctrldown)
    {
        // Change the box dimensions.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            w = ge->getBox()->getWidth();
            ge->getBox()->setWidth(w - 0.01);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            w = ge->getBox()->getWidth();
            ge->getBox()->setWidth(w + 0.01);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            h = ge->getBox()->getHeight();
            ge->getBox()->setHeight(h - 0.01);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            h = ge->getBox()->getHeight();
            ge->getBox()->setHeight(h + 0.01);
        }
    }
    else if (altdown)
    {
        /*// Change the window position.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            w = ge->getBox()->getWidth();
            ge->getBox()->setWidth(w - 0.01);
            h = ge->getBox()->getHeight();
            ge->getBox()->setHeight(h - 0.01);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            w = ge->getBox()->getWidth();
            ge->getBox()->setWidth(w + 0.01);
            h = ge->getBox()->getHeight();
            ge->getBox()->setHeight(h + 0.01);
        }*/
    }
    else if (shiftdown)
    {
        /*// Change the window dimensions.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            ge->getBox()->setVertexColor(0, 1.0*rand()/RAND_MAX, 1.0*rand()/RAND_MAX, 1.0*rand()/RAND_MAX);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            ge->getBox()->setVertexColor(1, 1.0*rand()/RAND_MAX, 1.0*rand()/RAND_MAX, 1.0*rand()/RAND_MAX);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            ge->getBox()->setVertexColor(2, 1.0*rand()/RAND_MAX, 1.0*rand()/RAND_MAX, 1.0*rand()/RAND_MAX);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            ge->getBox()->setVertexColor(3, 1.0*rand()/RAND_MAX, 1.0*rand()/RAND_MAX, 1.0*rand()/RAND_MAX);
        */
    }
    else
    {
        // Change the box position.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            ge->getBox()->getCenter(BoxCenter);
            ge->getBox()->setCenter(BoxCenter[0]-0.01, BoxCenter[1]);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            ge->getBox()->getCenter(BoxCenter);
            ge->getBox()->setCenter(BoxCenter[0]+0.01, BoxCenter[1]);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            ge->getBox()->getCenter(BoxCenter);
            ge->getBox()->setCenter(BoxCenter[0], BoxCenter[1]+0.01);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            ge->getBox()->getCenter(BoxCenter);
            ge->getBox()->setCenter(BoxCenter[0], BoxCenter[1]-0.01);
        }
    }
}
