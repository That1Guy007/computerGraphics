#include "CirclesAtts.h"

CirclesAtts::CirclesAtts(float cenx, float ceny, float cenz, float radius){
    Center[0] = cenx;
    Center[1] = ceny;
    Center[2] = cenz;
}

CirclesAtts::~CirclesAtts(){
//stuff
}

void CirclesAtts::setCenter(float cenx, float ceny, float cenz){
    Center[0] = cenx;
    Center[1] = ceny;
    Center[2] = cenz;
}

void CirclesAtts::setRadius(float radius){
    r = radius;
}

void CirclesAtts::setColor(float r, float g, float b, float a){
    Color[0] = r;
    Color[1] = g;
    Color[2] = b;
    Color[3] = a;
}

void CirclesAtts::setRotateAngle(float ang){
    rotateAng = ang; //turn into raions or deg?
}

void CirclesAtts::setRotateVec(float x, float y, float z){
    rotateVec[0] = x;
    rotateVec[1] = y;
    rotateVec[2] = z;
}

void CirclesAtts::getCenter(float* cen){
    cen[0] = Center[0];
    cen[1] = Center[1];
    cen[2] = Center[2];
}

float CirclesAtts::getRadius(){
    return r;
}

void CirclesAtts::getColor(float* col){
    col[0] = Color[0];
    col[1] = Color[1];
    col[2] = Color[2];
    col[3] = Color[3];
}

float CirclesAtts::getRotateAngle(){
    return rotateAng;
}

void CirclesAtts::getRotateVec(float* rot){
    rot[0] = rotateVec[0];
    rot[1] = rotateVec[1];
    rot[2] = rotateVec[2];
}
