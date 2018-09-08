#version 330 core

/**
\file AspectRatioVert.glsl

\brief Simple pass through vertex shader.

This is a simple GLSL pass through vertex shader.

\param [in] position --- vec4 position from vertex array.

\param [uniform] Projection --- mat4 projection matrix.

\param [uniform] modelmatrix --- mat4 model matrix.

*/

layout(location = 0) in vec4 position;

uniform mat4 Projection;
uniform mat4 ModelMatrix;

void main()
{
    gl_Position = Projection*ModelMatrix*position;
}
