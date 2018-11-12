#version 430 core
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
out vec4 out_position;
out vec3 out_normal;
out vec2 out_uv;

void main()
{
  out_position = model * vec4(in_position, 1);
  out_uv = in_uv;
  out_normal = mat3(normal) * in_normal;
  gl_Position = mvp * vec4(in_position, 1);
}
