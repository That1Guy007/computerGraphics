#ifndef SPHERICALCAMERA_H
#define SPHERICALCAMERA_H

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <math.h>

#include "ProgramDefines.h"

/**
\file SphericalCamera.h

\brief Header file for SphericalCamera.cpp

\author    Don Spickler,Carlos Hernandez
\version   1.2
\date      1/14/2018

*/

/**
\class SphericalCamera

\brief Creates a spherical camera, that is, one that sits on a sphere of radius r and always
points to the origin.

*/

class SphericalCamera
{
private:
    float r;      ///< Radius of camera to origin.
    float theta;  ///< Theta rotation on the xz plane counter clockwise from positive x axis.
    float psi;    ///< Psi rotation from the xz plane to radial.

public:
    SphericalCamera();
    void setPosition(float R, float Theta, float Psi);
    glm::vec3 getPosition();
    glm::mat4 lookAt();

    void addR(float num);
    void addTheta(float num);
    void addPsi(float num);

    void setR(float num);
    void setTheta(float num);
    void setPsi(float num);

    float getR();
    float getTheta();
    float getPsi();
};

#endif
