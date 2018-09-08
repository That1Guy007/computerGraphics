#include "loadShaders.h"
   /*
    *   Author: Carlos Hernandez
    *   Version: 1.0
    *   Date: 2/10/2018
    *
    */

const GLchar* ReaderShader(const char* filename){
    FILE* infile = fopen(filename, "rb");

    if(!infile){
        std::cerr<< "Failed to open file '" << filename << "'\n";
        return NULL;
    }

    fseek(infile, 0, SEEK_END);

    int len = ftell(infile);

    fseek(infile, 0,SEEK_SET);

    GLchar* source = new GLchar[len + 1];

    fread(source, 1, len, infile);
    fclose(infile);

    source[len]= 0;

    return  const_cast<const GLchar*>(source);
}

//return string for error report of the shader type
std::string getShaderString(GLenum type){
    std::string returnStr;

    if(type == GL_VERTEX_SHADER){
        returnStr = "vertex";
    }
    else if (type == GL_FRAGMENT_SHADER){
        returnStr = "Fragment";
    }
    else if (type == GL_GEOMETRY_SHADER){
        returnStr = "Geometry";
    }
    else if (type == GL_TESS_CONTROL_SHADER){
        returnStr = "Tessellation Control";
    }
    else if (type == GL_TESS_EVALUATION_SHADER){
        returnStr = "Tessellation Evaluation";
    }
    else{
        returnStr = "Unknown";
    }

    return returnStr;
}

GLuint loadShaderFromFile(shaderInfo* shaders){
    if(shaders == NULL){
        return 0;
    }
    GLuint program = glCreateProgram();

    shaderInfo* entry = shaders;

    while(entry->type != GL_NONE){
        GLuint shader = glCreateShader(entry->type);

        entry->shader = shader;

        const GLchar* source = ReaderShader(entry->filename);

        if(source == NULL){
            for(entry = shaders; entry->type != GL_NONE; ++entry){ //interesting
                glDeleteShader(entry->shader);
                entry->shader = 0;
            }

            return 0;
        }

        glShaderSource(shader, 1, &source, NULL);
        delete [] source;

        glCompileShader(shader);

        GLint compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

        if(!compiled){
            GLsizei len;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

            GLchar* log = new GLchar[len+1];
            glGetShaderInfoLog(shader, len, &len, log);
            std::cerr << "\n"<<getShaderString(entry->type) << " shader compilation unsuccessful:" << log<<"\n";
            delete [] log;
            return 0;
        }
       // std::cout << "\n"<<getShaderString(entry->type) << " shader compilation good:" <<"\n";

        glAttachShader(program, shader);
        ++entry;
    }
    glLinkProgram(program);

    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);

    if(!linked){
        GLsizei len;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

        GLchar* log = new GLchar[len+1];
        glGetProgramInfoLog(program, len, &len, log);
        //std::cerr<< "Shader link failed: " << log<<"\n";
        delete [] log;

        for(entry = shaders; entry->type != GL_NONE; ++entry){
            glDeleteShader(entry->shader);
            entry->shader = 0;
        }
        //std::cout<< "Shader link good: " <<"\n";

        return 0;
    }
    return program;
}


GLuint loadShaderFromMemory(shaderInfo* shaders)
{
    if (shaders == NULL)
        return 0;

    GLuint program = glCreateProgram();

    shaderInfo* entry = shaders;
    while (entry->type != GL_NONE)
    {
        GLuint shader = glCreateShader(entry->type);

        entry->shader = shader;

        const GLchar* source = (GLchar*)(entry->code.c_str());
        if (source == NULL)
        {
            for (entry = shaders; entry->type != GL_NONE; ++entry)
            {
                glDeleteShader(entry->shader);
                entry->shader = 0;
            }

            return 0;
        }

        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);

        GLint compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled)
        {
            GLsizei len;
            glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &len );

            GLchar* log = new GLchar[len+1];
            glGetShaderInfoLog( shader, len, &len, log );
            std::cerr << std::endl << getShaderString(entry->type) << " shader compilation failed: " << log << std::endl;
            delete [] log;
            return 0;
        }

        glAttachShader(program, shader);
        ++entry;
    }

    glLinkProgram(program);

    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked)
    {
        GLsizei len;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

        GLchar* log = new GLchar[len+1];
        glGetProgramInfoLog(program, len, &len, log);
        std::cerr << "Shader linking failed: " << log << std::endl;
        delete [] log;

        for (entry = shaders; entry->type != GL_NONE; ++entry)
        {
            glDeleteShader(entry->shader);
            entry->shader = 0;
        }

        return 0;
    }

    return program;
}


GLuint loadShaderFromFile(std::string vertfn, std::string fragfn)
{
    shaderInfo shaders[] =
    {
        {GL_VERTEX_SHADER, vertfn.c_str()},
        {GL_FRAGMENT_SHADER, fragfn.c_str()},
        {GL_NONE}
    };

    return loadShaderFromFile(shaders);
}



GLuint loadShaderFromMemory(std::string vertcode, std::string fragcode)
{
    shaderInfo shaders[] =
    {
        {GL_VERTEX_SHADER, "", vertcode},
        {GL_FRAGMENT_SHADER, "", fragcode},
        {GL_NONE}
    };

    return loadShaderFromMemory(shaders);
}
