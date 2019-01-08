#version 450 core

layout(location = 0) out vec4 out_color;

uniform sampler2D texture10;
uniform vec2 uScreen;

in vec2 out_uv;

void main()
{
    vec2 uv = floor(out_uv * (uScreen) ) / (uScreen) ;
    vec3 color = texture(texture10, uv).xyz;
    out_color.xyz = vec3(color.r * 0.3 + color.g * 0.45 + color.b * 0.25);
    out_color.w = 1;
}