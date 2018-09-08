#include "Circle.h"

/**
\file Circle.cpp
\brief Simple Circle object for drawing

Simple Circle object with OpenGL data loading and drawing interfaces.  The data that
is being stored is a single array of floats that represent the center vertex and then vertices
around the center, one vertex for each side with the first and last being the same vertex.
For each vertex, the array holds 5 floating point values of the form [r, g, b, x, y] where
the (r, g, b) is the color of the vertex and the (x, y) is the vertex position.

\author    Don Spickler, Carlos Hernandez
\version   1.2
\date      1/4/2018

*/

/**
\brief Constructor

Creates a Circle object, loads the attributes, generates the needed buffers
and IDs, and finally loads the object data up to the graphics card.

*/

Circle::Circle()
{
    radius = ((float) rand() / (float) RAND_MAX ) * 0.50;
    sides = 50;
    centerX = 0;
    centerY = 0;
    color[0] = 1;
    color[1] = 0;
    color[2] = 0;
    color[3] = 0;
    startsec = 0;
    vel[0] = 1 - 2*(GLfloat)rand()/RAND_MAX;
    vel[1] = 1 - 2*(GLfloat)rand()/RAND_MAX;
    startPOS[0] = 0;
    startPOS[1] = 0;

    std::cout<< radius<<"\n";
    glGenVertexArrays(1, &CircleVAO);
    glGenBuffers(1, &ArrayBuffer);
    glGenBuffers(1, &CircleEBO);
    glBindVertexArray(CircleVAO);

    vPosition = 0;
    vColor = 1;

    // Vertex and Color data for the box, using two triangles.

    GLfloat vertices[2*(sides+2)];

    for (int s = 0; s <= sides; s++)
    {
        vertices[2*s] = centerX + radius*cos((GLfloat)(s-1)/sides*(2*PI));
        vertices[2*s+1] = centerY + radius*sin((GLfloat)(s-1)/sides*(2*PI));
    }

    GLfloat vertexColors[3*(sides+2)];
    for (int s = 0; s <= sides+1; s++)
        for (int i = 0; i < 3; i++)
            vertexColors[3*s+i] = color[i];

    GLuint indices[sides+2];
    for (int i = 0; i < sides+2; i++)
        indices[i] = i;

    // Load the indexing array on the graphics card.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CircleEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Bind (turn on) the vertex buffer (storage location).
    glBindBuffer(GL_ARRAY_BUFFER, ArrayBuffer);

    // Allocate space for the vertex and color data. Do not load data at this point.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(vertexColors), NULL, GL_DYNAMIC_DRAW);

    // Load the vertex data.
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    // Load the color data.
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(vertexColors), vertexColors);

    // Setup vertex data position information. Note that the 5th parameter is 0, indicating tightly packed.
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    // Setup color data position information. Note that the 5th parameter is 0, indicating tightly packed.
    glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices)));

    // Set position indexes for shader streams.
    glEnableVertexAttribArray(vPosition);
    glEnableVertexAttribArray(vColor);
    //LoadDataToGraphicsCard();
}

/**
\brief Destructor

Clears the graphics memory.

*/

Circle::~Circle()
{
    glBindVertexArray(CircleVAO);
    glDeleteBuffers(1, &ArrayBuffer);
    glDeleteBuffers(1, &CircleEBO);
}

/**
\brief Resets the radius of the Circle.

\param r --- The radius of the Circle.

Resets the radius and then calls the data loading method.

*/

void Circle::setRadius(GLfloat r)
{
    radius = r;
}

/**
\brief Changes the color of the Circle.

\param r --- Red intensity for the Circle.
\param g --- Green intensity for the Circle.
\param b --- Blue intensity for the Circle.

Resets the color of the Circle to the new (r, g, b) value and calls the data loading method.

*/

void Circle::setColor(GLfloat r, GLfloat g,GLfloat b, GLfloat a)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
    color[3] = a;
}

/**
\brief Returns the radius of the Circle.

*/

GLfloat Circle::getRadius()
{
    return radius;
}


/**
\brief Populates the array c with the (x, y) coordinates of the center.

The array c must have length at least two.

*/

void Circle::getCenter(GLfloat* c)
{
    c[0] = center[0];
    c[1] = center[1];
}

void Circle::getColor(GLfloat* c){
    for(int i = 0; i < 4; i++){
        c[i] = color[i];
    }
}


void Circle::UpdatePosition(GLfloat bound[], float sec){

    float elap = sec - startsec;

    center[0] = startPOS[0] + elap * vel[0];
    center[1] = startPOS[1] + elap * vel[1];

    if (center[0] + radius > bound[1] ^ center[0] - radius < bound[0])
    {
        startPOS[0] = center[0];
        startPOS[1] = center[1];
        vel[0] = vel[0] * -1;
        startsec = sec;
        setColor((float)rand()/(float)RAND_MAX, (float)rand()/(float)RAND_MAX, (float)rand()/(float)RAND_MAX, 0);
    }
    if(center[1] + radius > bound[3] ^ center[1] - radius < bound[2]){
        startPOS[0] = center[0];
        startPOS[1] = center[1];
        vel[1] = vel[1] * -1;
        startsec = sec;
        setColor((float)rand()/(float)RAND_MAX, (float)rand()/(float)RAND_MAX, (float)rand()/(float)RAND_MAX, 0);

    }
//    else{
//        startPOS[0] = 0;
//        startPOS[1] = 0;
//        startsec = sec;
//    }

}
/**
\brief Draws the Circle to the OpenGL window.

*/

void Circle::draw()
{
    glBindVertexArray(CircleVAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CircleEBO);
    glDrawElements(GL_LINE_LOOP, sides + 1, GL_UNSIGNED_INT, NULL);
}
