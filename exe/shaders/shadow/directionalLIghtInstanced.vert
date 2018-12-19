#version 450 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_uv;
layout(location = 3) in mat4 in_instance_model;

uniform mat4 uLightVP;

void main()
{
  gl_Position = uLightVP * in_instance_model * vec4(in_position, 1);
}
