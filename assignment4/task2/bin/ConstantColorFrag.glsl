#version 330 core

/**
\file ConstantColorFrag.glsl

\brief Simple constant color shader.

\param ConstantColor --- uniform variable for a single color.

*/

uniform vec4 ConstantColor;
out vec4 col;

void main()
{
    col = ConstantColor;
}
