#include "UI.h"

/**
\file UI.cpp
\brief User interface processor for the program.

\author    Don Spickler, Carlos Hernandez
\version   1.2
\date      12/28/2017

*/

/**
\brief Constructor

\param graph --- Pointer to the GraphicsEngine that this interface processor is attached.

Simply stores the pointer of the GraphicsEngine.

*/

UI::UI(GraphicsEngine* graph)
{
    ge = graph;
    mouseDown = false;
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

        if (event.type == sf::Event::MouseMoved)
            processMouseMoved(event.mouseMove);

        if (event.type == sf::Event::MouseButtonPressed)
            processMouseButtonPressed(event.mouseButton);

        if (event.type == sf::Event::MouseButtonReleased)
            processMouseButtonReleased(event.mouseButton);

    }

    // Process the state of the keyboard outside of event firing,
    keyboardStateProcessing();

}

/**
\brief Method that takes in the integer mouse position coordinates from a mouse event
and converts them into screen coordinates.

It is assumed that the array screenBounds holds the bounds to the screen in the form
(l, r, b, t).

\param mousePosition --- A sf::Vector2i holding the x and y positions taken from the
mouse position coordinates of a mouse event.

\return A sf::Vector2f holding the screen (x, y) position of the mouse.

*/

sf::Vector2f UI::MouseToScreenConversion(sf::Vector2i mousePosition)
{
    sf::Vector2f sc;
    float* screenBounds = ge->getScreenBounds();

    sc.x = (float)mousePosition.x / ge->getSize().x * (screenBounds[1] - screenBounds[0]) + screenBounds[0];
    sc.y = screenBounds[3] - (float)mousePosition.y / ge->getSize().y * (screenBounds[3] - screenBounds[2]);

    return sc;
}

/**
\brief The method outputs the position of the mouse on a move event and if the system is
in a click and drag mode it will resize the box about the center with the cursor being
on the green vertex.

\param mouseMoveEvent --- The SFML mouse move event structure.

*/

void UI::processMouseMoved(sf::Event::MouseMoveEvent mouseMoveEvent)
{
    sf::Vector2f sc = MouseToScreenConversion(sf::Vector2i(mouseMoveEvent.x, mouseMoveEvent.y));
    float bc[2];
    ge->getBox()->getCenter(bc);
    if((sc.x <= bc[0] + (ge->getBox()->getWidth() / 2) && sc.x >= bc[0] + -1 *(ge->getBox()->getWidth() / 2) ) &&
           ((sc.y <= bc[1] + ge->getBox()->getHeight() / 2) && (sc.y >= bc[1] + -1 * ge->getBox()->getWidth() / 2)) ){
        ge->getBox()->setVertexColor(0, 1, 0, 0);
        ge->getBox()->setVertexColor(1, 1, 0, 0);
        ge->getBox()->setVertexColor(2, 1, 0, 0);
        ge->getBox()->setVertexColor(3, 1, 0, 0);
    }
    if( !( (sc.x <= bc[0] + ge->getBox()->getWidth() / 2 && sc.x >= bc[0] + -1 *(ge->getBox()->getWidth() / 2) ) &&
           ((sc.y <= bc[1] + ge->getBox()->getHeight() / 2) && (sc.y >= bc[1] + -1 * ge->getBox()->getWidth() / 2)) ) ){
        ge->getBox()->setVertexColor(0, 1, 0, 0);
        ge->getBox()->setVertexColor(1, 0, 1, 0);
        ge->getBox()->setVertexColor(2, 0, 0, 1);
        ge->getBox()->setVertexColor(3, 1, 1, 1);
    }

    if (mouseDown)
        std::cout << "Drag ~ " << "x: "<< clickX << ", y: "<<clickY << " ~ ";
    std::cout << "Moved: (" << mouseMoveEvent.x << ", " << mouseMoveEvent.y << ")" << "  ~  (" << sc.x << ", " << sc.y << ")" << std::endl;

    if (mouseDown)
    {
        float xComp = -1 * (clickX - sc.x);
        float yComp = -1 * (clickY - sc.y);
        //float bc[2];
        //ge->getBox()->getCenter(bc);
        float newCx = (center[0] + xComp);
        float newCy = (center[1] + yComp);
        ge->getBox()->setCenter(newCx,newCy);
        //ge->getBox()->setHeight(newh);
        //ge->getBox()->setWidth(neww);
    }
}

/**
\brief The method outputs the position and the button pressed of the mouse on a button event.

It also updates the box by centering it on the cursor if the click was a left click and
adjusting the size of the box on a right click.  On the right click the box will be adjusted
so that the green corner of the box will be on the cursor.

\param mouseButtonEvent --- The SFML mouse button event structure.

*/

void UI::processMouseButtonPressed(sf::Event::MouseButtonEvent mouseButtonEvent)
{
    std::string button = "";
    if (mouseButtonEvent.button == sf::Mouse::Left)
        button = "Left";
    else if (mouseButtonEvent.button == sf::Mouse::Right)
        button = "Right";
    else if (mouseButtonEvent.button == sf::Mouse::Middle)
        button = "Middle";

    sf::Vector2f sc = MouseToScreenConversion(sf::Vector2i(mouseButtonEvent.x, mouseButtonEvent.y));
    std::cout<<"width: "<< ge->getBox()->getWidth()<<"\n";
    std::cout << "Pressed: " << button << ": (" << mouseButtonEvent.x << ", " << mouseButtonEvent.y << ")"  << "  ~  (" << sc.x << ", " << sc.y << ")" << std::endl;

    if (mouseButtonEvent.button == sf::Mouse::Left)
    {
        float bc[2];
        ge->getBox()->getCenter(bc);
        //make sure that the click is within the box
        if( (sc.x <= bc[0] + ge->getBox()->getWidth() / 2 && sc.x >= bc[0] + -1 *(ge->getBox()->getWidth() / 2) ) &&
           ((sc.y <= bc[1] + ge->getBox()->getHeight() / 2) && (sc.y >= bc[1] + -1 * ge->getBox()->getWidth() / 2)) ){
            //set the center based on the mouse movement. mouse moves so does center
            //ge->getBox()->setCenter(sc.x, sc.y);
            clickX = sc.x;
            clickY = sc.y;
            ge->getBox()->getCenter(center);
            mouseDown = true;
        }
    }
}

/**
\brief The method simply outputs the position and the button released of the mouse
on a button event.

\param mouseButtonEvent --- The SFML mouse button event structure.

*/

void UI::processMouseButtonReleased(sf::Event::MouseButtonEvent mouseButtonEvent)
{
    std::string button = "";
    if (mouseButtonEvent.button == sf::Mouse::Left)
        button = "Left";
    else if (mouseButtonEvent.button == sf::Mouse::Right)
        button = "Right";
    else if (mouseButtonEvent.button == sf::Mouse::Middle)
        button = "Middle";

    sf::Vector2f sc = MouseToScreenConversion(sf::Vector2i(mouseButtonEvent.x, mouseButtonEvent.y));

    std::cout << "Released: " << button << ": (" << mouseButtonEvent.x << ", " << mouseButtonEvent.y << ")"  << "  ~  (" << sc.x << ", " << sc.y << ")" << std::endl;

    if (mouseButtonEvent.button == sf::Mouse::Left)
        mouseDown = false;
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

*/

void UI::keyPressed(sf::Event::KeyEvent keyevent)
{
    int key = keyevent.code;
    bool ctrldown = keyevent.control;

    if (ctrldown)
    {
        // Reset the box size.
        if (key == sf::Keyboard::R)
        {
            ge->getBox()->setWidth(1);
            ge->getBox()->setHeight(1);
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

If the control or Z key is down:

- Left: Decreases the width of the box.
- Right: Increases the width of the box.
- Up: Decreases the height of the box.
- Down: Increases the height of the box.

*/

void UI::keyboardStateProcessing()
{
    GLfloat BoxCenter[2];
    float w, h;
    sf::Vector2i wp;
    sf::Vector2u ws;

    bool ctrldown = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);

    if (ctrldown || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
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
