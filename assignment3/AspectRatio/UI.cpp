#include "UI.h"

/**
\file UI.cpp
\brief User interface processor for the program.

\author    Don Spickler Carlos Hernandez
\version   1.2.1
\date      2/23/2018

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
    srand(clock());
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

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)){
            cntrl = true;
        }
        else{
            cntrl = false;
        }


        if (event.type == sf::Event::MouseMoved)
            processMouseMoved(event.mouseMove);

        if (event.type == sf::Event::MouseButtonPressed)
            processMouseButtonPressed(event.mouseButton);

        if (event.type == sf::Event::MouseButtonReleased)
            processMouseButtonReleased(event.mouseButton);
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
        ge->getBox(boxnum)->setVertexColor(0, 1, 0.3, 0.21);
        break;

    // F2 Sets vertex 0 of the box to (1, 0.3, 0.21)
    case sf::Keyboard::F2:
        ge->getBox(boxnum)->setVertexColor(1, 1, 0.3, 0.21);
        break;

    // F5 Resets the box center to (0, 0)
    case sf::Keyboard::F5:
        ge->getBox(boxnum)->setCenter(0, 0);
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
        ge->getBox(boxnum)->getCenter(BoxCenter);
        ge->getBox(boxnum)->setCenter(BoxCenter[0]-0.01, BoxCenter[1]);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        ge->getBox(boxnum)->getCenter(BoxCenter);
        ge->getBox(boxnum)->setCenter(BoxCenter[0]+0.01, BoxCenter[1]);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        ge->getBox(boxnum)->getCenter(BoxCenter);
        ge->getBox(boxnum)->setCenter(BoxCenter[0], BoxCenter[1]+0.01);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        ge->getBox(boxnum)->getCenter(BoxCenter);
        ge->getBox(boxnum)->setCenter(BoxCenter[0], BoxCenter[1]-0.01);
    }
}

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
    //std::cout<<"width: "<< ge->getBox()->getWidth()<<"\n";
    std::cout << "Pressed: " << button << ": (" << mouseButtonEvent.x << ", " << mouseButtonEvent.y << ")"  << "  ~  (" << sc.x << ", " << sc.y << ")" << std::endl;

    if (mouseButtonEvent.button == sf::Mouse::Right && cntrl)
    {

       if(checkLocation(counter, sc.x, sc.y)){

            float sidelength = 0.10 + (((float)rand()/(float)RAND_MAX )*  0.20);
            float bc[2];
            std::cout<<"click: "<<sc.x << " " <<sc.y << "\n";
            ge->getBox(counter)->setCenter(sc.x, sc.y);
            ge->getBox(counter)->setWidth(sidelength);
            ge->getBox(counter)->setHeight(sidelength);
            ge->getBox(counter)->setVertexColor(0, (((float)rand()/(float)RAND_MAX )), (((float)rand()/(float)RAND_MAX )), (((float)rand()/(float)RAND_MAX )) );
            ge->getBox(counter)->setVertexColor(1, (((float)rand()/(float)RAND_MAX )), (((float)rand()/(float)RAND_MAX )), (((float)rand()/(float)RAND_MAX )) );
            ge->getBox(counter)->setVertexColor(2, (((float)rand()/(float)RAND_MAX )), (((float)rand()/(float)RAND_MAX )), (((float)rand()/(float)RAND_MAX )) );
            ge->getBox(counter)->setVertexColor(3, (((float)rand()/(float)RAND_MAX )), (((float)rand()/(float)RAND_MAX )), (((float)rand()/(float)RAND_MAX )) );
            storeLocation(counter, sc.x, sc.y, sidelength);

            counter = (counter + 1) % 100;
        }
        else{
            storeLocation(box2Del, 0, 0, 0);
            ge->getBox(box2Del)->setCenter(0, 0);
            ge->getBox(box2Del)->setWidth(0);
            ge->getBox(box2Del)->setHeight(0);
        }

        ge->display();
    }
}

bool UI::checkLocation(int maxSquares, float x, float y){
    bool noBox = true;
    for(int i = 0; i < maxSquares; i++){
            std::cout<<locationArray[i * 3] + locationArray[i*3 + 2] / 2<< ", "<<locationArray[i * 3] - locationArray[i*3 + 2] / 2 << ", "
            << locationArray[i * 3 +1] + locationArray[i*3 + 2] / 2<< ", " << locationArray[i * 3 + 1] - locationArray[i*3 + 2] / 2<<"\n";
       if(noBox){
            if((x > (locationArray[i * 3] + locationArray[i*3 + 2] / 2 ) || x < (locationArray[i * 3] - locationArray[i*3 + 2] / 2 )) ||
                 (y > (locationArray[i * 3 +1] + locationArray[i*3 + 2] / 2 ) || y < (locationArray[i * 3 + 1] - locationArray[i*3 + 2] / 2  ))  ){
                     std::cout<<"TRUE\n";
                noBox = true;
            }
            else{
                noBox = false;
            }
        }
        else{
            std::cout<<"FALSE\n";
            box2Del = i;
            break;
        }
    }
    std::cout<<"DONE?\n";
    return noBox;
}

void UI::storeLocation(int sqNum, float centX, float centY, float side){
    locationArray[sqNum * 3] = centX;
    locationArray[sqNum * 3 + 1] = centY;
    locationArray[sqNum * 3 + 2] = side;
}

/**
\brief The method simply outputs the position and the button released of the mouse
on a button event.

\param mouseButtonEvent --- The SFML mouse button event structure.

*/

void UI::processMouseButtonReleased(sf::Event::MouseButtonEvent mouseButtonEvent)
{

}
