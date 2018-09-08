#ifndef LOADSHADERS_H
#define LOADSHADERS_H

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <GL/glew.h>
#endif // __APPLE__

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>


/**
\file LoadShaders.h
\brief Header file for LoadShaders.cpp

\author    Don Spickler, Carlos Hernandez
\version   1.1
\date      Written: 11/21/2015  <BR>
Revised: 11/21/2015

*/


/**
\struct ShaderInfo

\brief Structure that holds shader information.

*/

typedef struct
{
    GLenum type;  ///< Type of shader, GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, ...
    const char* filename;  ///< Filename of shader code file, if loading from a file. Set to "" if loading from memory.
    const std::string code; ///< Code string of shader code, if loading from memory. Set to "" (or ignore) if loading from a file.
    GLuint shader; ///< Output storage for glCreateShader function, not needed as input from user.
} ShaderInfo;

GLuint LoadShadersFromFile(ShaderInfo*);
GLuint LoadShadersFromMemory(ShaderInfo*);
GLuint LoadShadersFromFile(std::string, std::string);
GLuint LoadShadersFromMemory(std::string, std::string);
std::string getShaderString(GLenum);

#endif // LOADSHADERS_H