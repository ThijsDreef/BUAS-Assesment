#version 450 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_uv;
layout(std140, binding = 1) buffer MatrixBuffer
{
  mat4 mvp;
  mat4 modelView;
  mat4 normal;
  mat4 model;
};

uniform mat4 uLightVP;

void main()
{
  gl_Position = uLightVP * model * vec4(in_position, 1);
}
