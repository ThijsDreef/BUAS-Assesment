#version 430 core
layout (location = 0) out vec4 rPosition;
layout (location = 1) out vec3 rNormal;
layout (location = 2) out vec4 rColor;

layout(std140, binding = 0) uniform MaterialBuffer
{
  vec4 color;
  uint textureId;
};

uniform sampler2D texture10;

in vec4 out_position;
in vec3 out_normal;
in vec2 out_uv;

void main(void)
{
  rPosition = out_position;
  rNormal = out_normal;
  rColor = (textureId < 1000) ? texture(texture10, out_uv) + 0.2 : color;
}
