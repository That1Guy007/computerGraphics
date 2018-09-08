#version 330 core

/**
\file PassThroughFrag.glsl

\brief Simple pass through fragment shader.

This is a simple GLSL pass through fragment shader.

\param [in] color --- vec4 color from vertex shader.

\param [out] fColor --- vec4 output color to the frame buffer.

*/

in  vec4 color;
in vec4 colorConst;
out vec4 fColor;
out vec4 colors;

void main()
{
    fColor = color;
    colors = colorConst;
}
