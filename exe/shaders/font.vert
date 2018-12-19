#version 450 core
layout(location = 0) in vec2 in_position;
layout(location = 1) in vec2 in_uv;

uniform mat4 mvp;

out vec2 out_uv;
void main()
{
    out_uv = in_uv;
    gl_Position = mvp * vec4(vec3(in_position, 0.5), 1);
}