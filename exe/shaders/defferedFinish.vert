#version 430 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_uv;

out vec2 out_uv;
void main()
{
  out_uv = vec2(in_uv.x, 1.0 - in_uv.y);
  gl_Position = vec4(in_position + vec3(0, 0, 1), 1);
}
