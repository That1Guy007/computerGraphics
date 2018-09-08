#version 330 core

/**
\file PassThroughFrag.glsl

\brief Simple pass through fragment shader.

This is a simple GLSL pass through fragment shader.

\param [uniform] color --- vec4 color from vertex shader.

*/

uniform vec4 color;
out vec4 col;

void main()
{
    col = color;
}
