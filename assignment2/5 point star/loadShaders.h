#ifndef LOADSHADERS_H_INCLUDED
#define LOADSHADERS_H_INCLUDED

#include <GL/glew.h>

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>

typedef struct{
    //type of shader
    GLenum type;

    //filename of shader if loading from a file, otherwise "" to load form memory
    const char* filename;

    //string of code, loading from mem, set to "", otherwise ignore if loading from file
    const std::string code;

    //Output storage for glCreateShader function, not needed as input from user
    GLuint shader;
}   shaderInfo;

GLuint loadShaderFromFile(shaderInfo*);
GLuint loadShaderFromMemory(shaderInfo*);
GLuint loadShaderFromFile(std::string, std::string);
GLuint loadShaderFromMemory(std::string, std::string);
std::string getShaderString(GLenum);

#endif // LOADSHADERS_H_INCLUDED
