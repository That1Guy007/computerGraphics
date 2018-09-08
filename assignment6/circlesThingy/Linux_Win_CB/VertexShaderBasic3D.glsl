#version 400 core

/**
\file VertexShaderBasic3D.glsl

\brief Vertex shader that incorporates the transformation of vertices
by a projection*view*model matrix.

\param [in] position --- vec4 vertex position from memory.

\param [in] icolor --- vec4 vertex color from memory.

\param [out] color --- vec4 output color to the fragment shader.

\param [uniform] PVM --- mat4 transformation matrix in the form projection*view*model.

*/

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 icolor;

uniform mat4 Proj;
uniform mat4 View;
uniform mat4 Model;
uniform vec4 incolor;

out vec4 color;
out vec4 colorConst;

void main()
{
    color = icolor;
    colorConst = incolor;
    gl_Position = Proj * View * Model * position;
}
