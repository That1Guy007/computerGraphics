#include "Axes2D.h"

/**
\file Axes2D.cpp
\brief Simple 2-D axes object for drawing

Simple 2-D axes object with OpenGL data loading and drawing interfaces.  The data that
is being stored is a created in two separate arrays, one for vertices and the other for
color.  These blocks of data are transferred to a single array buffer on the graphics
card in two separate locations (that is the data is not intermixed) and hence we can
set up the reading pointers as having tightly packed data. There is also an index array
for drawing the axes lines.

\author    Don Spickler
\version   1.1
\date      1/7/2018

*/

/**
\brief Constructor

\param XExt --- The extent of the x-axis.
\param YExt --- The extent of the y-axis.

Creates the object, loads the attributes, generates the needed buffers and IDs, and finally
loads the object data up to the graphics card.

*/

Axes2D::Axes2D(GLfloat XExt, GLfloat YExt)
{
    XExtent = XExt;
    YExtent = YExt;
    XAxisColor[0] = 1;
    XAxisColor[1] = 0;
    XAxisColor[2] = 0;
    YAxisColor[0] = 0;
    YAxisColor[1] = 1;
    YAxisColor[2] = 0;

    glGenVertexArrays(1, &BoxVAO);
    glGenBuffers(1, &ArrayBuffer);
    glGenBuffers(1, &BoxEBO);

    LoadDataToGraphicsCard();
}

/**
\brief Destructor

Clears the graphics memory used for the rectangle.

*/

Axes2D::~Axes2D()
{
    glBindVertexArray(BoxVAO);
    glDeleteBuffers(1, &ArrayBuffer);
    glDeleteBuffers(1, &BoxEBO);
}

/**
\brief Loads the axes data to the graphics card.

Creates an array of vertex positions and colors from the data stored in the object,
creates an index array, allocates graphics memory for the arrays and loads the arrays
into graphics memory. Finally, it sets up pointers to the vertex and color data in
the two arrays.

*/

void Axes2D::LoadDataToGraphicsCard()
{
    vPosition = 0;
    vColor = 1;

    // Vertex and Color data for the box, using two triangles.

    GLfloat vertices[16];

    vertices[0] = 0;
    vertices[1] = 0;
    vertices[2] = -XExtent;
    vertices[3] = 0;

    vertices[4] = 0;
    vertices[5] = 0;
    vertices[6] = XExtent;
    vertices[7] = 0;

    vertices[8] = 0;
    vertices[9] = 0;
    vertices[10] = 0;
    vertices[11] = -YExtent;

    vertices[12] = 0;
    vertices[13] = 0;
    vertices[14] = 0;
    vertices[15] = YExtent;

    GLfloat colors[24];

    colors[0] = XAxisColor[0]/2;
    colors[1] = XAxisColor[1]/2;
    colors[2] = XAxisColor[2]/2;
    colors[3] = XAxisColor[0]/2;
    colors[4] = XAxisColor[1]/2;
    colors[5] = XAxisColor[2]/2;

    colors[6] = XAxisColor[0];
    colors[7] = XAxisColor[1];
    colors[8] = XAxisColor[2];
    colors[9] = XAxisColor[0];
    colors[10] = XAxisColor[1];
    colors[11] = XAxisColor[2];

    colors[12] = YAxisColor[0]/2;
    colors[13] = YAxisColor[1]/2;
    colors[14] = YAxisColor[2]/2;
    colors[15] = YAxisColor[0]/2;
    colors[16] = YAxisColor[1]/2;
    colors[17] = YAxisColor[2]/2;

    colors[18] = YAxisColor[0];
    colors[19] = YAxisColor[1];
    colors[20] = YAxisColor[2];
    colors[21] = YAxisColor[0];
    colors[22] = YAxisColor[1];
    colors[23] = YAxisColor[2];

    GLuint indices[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    // Bind (turn on) a vertex array.
    glBindVertexArray(BoxVAO);

    // Load the indexing array on the graphics card.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BoxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Bind (turn on) the vertex buffer (storage location).
    glBindBuffer(GL_ARRAY_BUFFER, ArrayBuffer);

    // Allocate space for the vertex and color data. Do not load data at this point.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_DYNAMIC_DRAW);

    // Load the vertex data.
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    // Load the color data.
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);

    // Setup vertex data position information. Note that the 5th parameter is 0, indicating tightly packed.
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    // Setup color data position information. Note that the 5th parameter is 0, indicating tightly packed.
    glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices)));

    // Set position indexes for shader streams.
    glEnableVertexAttribArray(vPosition);
    glEnableVertexAttribArray(vColor);
}

/**
\brief Sets the extent of the x-axis.

\param e --- The new extent.

Sets the extent of the x-axis and then calls the data loading method.

*/

void Axes2D::setXExtent(GLfloat e)
{
    XExtent = e;
    LoadDataToGraphicsCard();
}

/**
\brief Sets the extent of the y-axis.

\param e --- The new extent.

Sets the extent of the y-axis and then calls the data loading method.

*/

void Axes2D::setYExtent(GLfloat e)
{
    YExtent = e;
    LoadDataToGraphicsCard();
}


/**
\brief Changes the color of the x-axis.

\param r --- Red intensity for the axis.
\param g --- Green intensity for the axis.
\param b --- Blue intensity for the axis.

Sets the color of the axis to the new (r, g, b) value and calls the data loading method.

*/

void Axes2D::setXAxisColor(GLfloat r, GLfloat g, GLfloat b)
{
    XAxisColor[0] = r;
    XAxisColor[1] = g;
    XAxisColor[2] = b;

    LoadDataToGraphicsCard();
}

/**
\brief Changes the color of the y-axis.

\param r --- Red intensity for the axis.
\param g --- Green intensity for the axis.
\param b --- Blue intensity for the axis.

Sets the color of the axis to the new (r, g, b) value and calls the data loading method.

*/

void Axes2D::setYAxisColor(GLfloat r, GLfloat g, GLfloat b)
{
    YAxisColor[0] = r;
    YAxisColor[1] = g;
    YAxisColor[2] = b;

    LoadDataToGraphicsCard();
}

/**
\brief Returns the x-axis extent.

*/

GLfloat Axes2D::getXExtent()
{
    return XExtent;
}

/**
\brief Returns the y-axis extent.

*/

GLfloat Axes2D::getYExtent()
{
    return YExtent;
}

/**
\brief Draws the axes to the OpenGL window.

*/

void Axes2D::draw()
{
    glBindVertexArray(BoxVAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BoxEBO);
    glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, NULL);
}
