#include "Star.h"

/**
\file Star.cpp

\brief Class file for Star.cpp

\author    Don Spickler, Carlos Hernandez
\version   1.3.1
\date      3/2/2018

*/

/**
\class Star

\brief The Star class holds position and color data for a multicolored star.  It also has
facilities for loading the data to the graphics card and invoking draw commands on the data.

*/
/**
\brief Constructor

\param cx --- X position of the center.
\param cx --- Y position of the center.
\param r --- The radius of the star.
\param s --- The # of points on the star.

Creates a star object, loads the attributes, enables GLEW, generates the needed buffers
and IDs, and finally loads the object data up to the graphics card.

*/

Star::Star(GLfloat cx, GLfloat cy, GLfloat r, GLint s)
{
    centerX = cx;
    centerY = cy;
    radius = .4;
    points = s;
    color[0] = 1;
    color[1] = 0;
    color[2] = 0;
    centerColor[0] = 1;
    centerColor[1] = 1;
    centerColor[2] = 1;
    glGenVertexArrays(1, &StarVAO);
    glGenBuffers(1, &ArrayBuffer);
    glGenBuffers(1, &StarEBO);

    srand(time(NULL));

    LoadDataToGraphicsCard();
}

/**
\brief Destructor

Clears the graphics memory used for the star.

*/

Star::~Star()
{
    glBindVertexArray(StarVAO);
    glDeleteBuffers(1, &ArrayBuffer);
    glDeleteBuffers(1, &StarEBO);
}
/**
 \brief LoadDataToGraphicsCard()
 loads da data
*/

void Star::LoadDataToGraphicsCard(){
    points = rand() % 21 + 5;
    points = points * 6;
    //std::cout<<points<< "\n";
    GLfloat vertData[(points+2) * 10] = {};//outer + inner points + center
    GLuint indices[points +2];
    int Count = 1;

    for(int i = 0; i<points +1; i++){
        //indices[i] = i;
        if(i % 3 == 0){
            indices[i] = 0;
        }
        else if(i % 3 == 1){
            indices[i] = indices[i - 1] + Count;
            Count++;
        }
        else{
            indices[i] = indices[i -1] + 1;
        }
        std::cout<<indices[i]<<"\n";
    }

    vertData[3] = centerX;//center x
    vertData[4] = centerY;//center Y

    for(int i = 0; i < 3; i++){
        vertData[i] = centerColor[i];
    }

    for(int i = 1; i <= points + 1; i++){
       for(int x = 0; x < 3; x++){
            vertData[5 * i + x] = color[x];
       }
       if(i % 2 == 1){
            vertData[5 * i + 3] = centerX + radius * cos((PI/2) + ( (GLfloat)(i-1) / (points/6) * ( PI) ));
            vertData[5 * i + 4] = centerY + radius * sin((PI/2) + ( (GLfloat)(i-1) / (points/6) * ( PI) ));
       }
       else{
            vertData[5 * i + 3] = centerX + radius/2 * (cos((PI/2) + ( (GLfloat)(i-1) / (points/6) * ( PI) )) );
            vertData[5 * i + 4] = centerY + radius/2 * sin((PI/2) + ( (GLfloat)(i-1) / (points/6) * ( PI) )) ;
       }
       std::cout<<vertData[5 * i + 3] << ", "<< vertData[5 * i + 4]<< "\n";
    }

    glBindVertexArray(StarVAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, StarEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, ArrayBuffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertData), vertData, GL_STATIC_DRAW);

    //Load position data for star
    /*glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertData), vertData);

    //Load colors for the tips
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertData), sizeof(color), color); */

    /*//Load center color data
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertData) + sizeof(color), sizeof(centerColor), centerColor);//*/

    glVertexAttribPointer(1 /* position of color?*/, 3, GL_FLOAT, GL_TRUE, 5 * sizeof(GLfloat), BUFFER_OFFSET(0));

    glVertexAttribPointer(0 /* position of verts */, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), BUFFER_OFFSET(3 * sizeof(GLfloat)));

    glEnableVertexAttribArray(0); //verts
    glEnableVertexAttribArray(1); //color
}
/**
\brief setRadius
 Sets the radius of the star object.
 loads to graphics.
*/

void Star::setRadius(GLfloat r)
{
    radius = r;
    LoadDataToGraphicsCard();
}
/**
\brief setPoints
 Sets the points of the star object.
 loads to graphics.
*/
void Star::setPoints(GLint s)
{
    points = s;
    LoadDataToGraphicsCard();
}
/**
\brief setCenter
 Sets the Center of the star object.
 loads to graphics.
*/

void Star::setCenter(GLfloat cx, GLfloat cy)
{
    centerX = cx;
    centerY = cy;
    LoadDataToGraphicsCard();
}
/**
\brief setPointColor
 Sets the color of the points of the star object.
 loads to graphics.
*/
void Star::setPointColor(GLfloat r, GLfloat g, GLfloat b)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
    LoadDataToGraphicsCard();
}
/**
\brief setCenterColor
 Sets the color of the center of the star object.
 loads to graphics.
*/
void Star::setCenterColor(GLfloat r, GLfloat g, GLfloat b)
{
    centerColor[0] = r;
    centerColor[1] = g;
    centerColor[2] = b;
    LoadDataToGraphicsCard();
}
/**
\brief getRadius
 Gets the radius of the star object.
*/
GLfloat Star::getRadius()
{
    return radius;
}

GLint Star::getPoints()
{
    return points;
}
/**
\brief getCenter
 Gets the center of the star object.
*/
void Star::getCenter(GLfloat* c)
{
    c[0] = centerX;
    c[1] = centerY;
}
/**
\brief draw
 Draw the star object.
*/
void Star::draw()
{
    glBindVertexArray(StarVAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, StarEBO);
    glDrawElements(GL_TRIANGLES, (points + 2), GL_UNSIGNED_INT, NULL);
}
