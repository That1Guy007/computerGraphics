#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include "GraphicsEngine.h"

/**
\file UI.h

\brief Header file for UI.cpp

\author    Don Spickler
\version   1.2
\date      1/7/2018

*/

/**
\class UI

\brief The UI class handles the user interface event processing for the program.  It
contains a pointer to the graphics engine as the communication link to the graphics
and scene objects.

*/

class UI
{
private:
    GraphicsEngine* ge;  ///< Pointer to the GraphicsEngine that this processor is attached.
    int boxnum, box2Del, counter = 0;          ///< Number of the box to be altered.
    bool mouseDown;      ///< Boolean tracking of the left mouse button.
    float clickX, clickY, center[2], locationArray[300];
    bool cntrl;


    void processMouseMoved(sf::Event::MouseMoveEvent mouseMoveEvent);
    void processMouseButtonPressed(sf::Event::MouseButtonEvent mouseButtonEvent);
    void processMouseButtonReleased(sf::Event::MouseButtonEvent mouseButtonEvent);
    sf::Vector2f MouseToScreenConversion(sf::Vector2i mousePosition);
    void keyPressed(sf::Event::KeyEvent keyevent);
    void keyboardStateProcessing();
    bool checkLocation(int, float, float);
    void storeLocation(int, float, float, float);

public:
    UI(GraphicsEngine* graph);
    ~UI();

    void processEvents();
};

#endif // UI_H_INCLUDED
