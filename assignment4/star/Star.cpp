#include "Star.h"

/*
  Author: Don Spickler, Carlos Hernandez
  Date: 3/02/2018
  version: 1.2.1
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
    glGenVertexArrays(1, &StarVAO);
    glGenBuffers(1, &ArrayBuffer);
    glGenBuffers(1, &StarEBO);

    srand(time(NULL));

    LoadDataToGraphicsCard();
}

Star::~Star()
{
    glBindVertexArray(StarVAO);
    glDeleteBuffers(1, &ArrayBuffer);
    glDeleteBuffers(1, &StarEBO);
}

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

    vertData[3] = 0;//center x
    vertData[4] = 0;//center Y

    for(int i = 0; i < 3; i++){
        vertData[i] = color[i];
    }

    for(int i = 1; i <= points + 1; i++){
       for(int x = 0; x < 3; x++){
            vertData[5 * i + x] = color[x];
       }
       if(i % 2 == 1){
            vertData[5 * i + 3] = centerX + cos((PI/2) + ( (GLfloat)(i-1) / (points/6) * ( PI) ));
            vertData[5 * i + 4] = centerY + sin((PI/2) + ( (GLfloat)(i-1) / (points/6) * ( PI) ));
       }
       else{
            vertData[5 * i + 3] = centerX + radius * (cos((PI/2) + ( (GLfloat)(i-1) / (points/6) * ( PI) )) );
            vertData[5 * i + 4] = centerY + radius * sin((PI/2) + ( (GLfloat)(i-1) / (points/6) * ( PI) )) ;
       }
       std::cout<<vertData[5 * i + 3] << ", "<< vertData[5 * i + 4]<< "\n";
        /*if(i % 4 == 2){
            vertData[i].x = cos((PI/2) + ( (i-1) * PI / (2 * points)));
        }
        else if (i % 4 == 3){
            vertData[i].y = sin((PI/2) + ( (i-1) * PI / (2 * points)));
        }
        else if( i % 4 == 0){
            vertData[i].x = cos((PI/2) + ( (i-1) * PI / points));
        }
        else{
            vertData[i].y = sin((PI/2) + ( (i-1) * PI / points));
        }*/
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

void Star::setRadius(GLfloat r)
{

}

void Star::setPoints(GLint s)
{

}

void Star::setCenter(GLfloat cx, GLfloat cy)
{

}

void Star::setPointColor(GLfloat r, GLfloat g, GLfloat b)
{

}

void Star::setCenterColor(GLfloat r, GLfloat g, GLfloat b)
{

}

GLfloat Star::getRadius()
{

}

GLint Star::getPoints()
{

}

void Star::getCenter(GLfloat* c)
{

}

void Star::draw()
{
    glBindVertexArray(StarVAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, StarEBO);
    glDrawElements(GL_TRIANGLES, (points + 2), GL_UNSIGNED_INT, NULL);
}
