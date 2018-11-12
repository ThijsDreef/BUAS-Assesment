#version 430 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_uv;
layout(location = 3) in mat4 in_instance_model;

uniform mat4 p;

out vec4 out_position;
out vec3 out_normal;
out vec2 out_uv;

void main()
{
  out_position = in_instance_model * vec4(in_position, 1);
  out_uv = in_uv;
  out_normal = in_normal;
  gl_Position = p * in_instance_model *  vec4(in_position, 1);
}
