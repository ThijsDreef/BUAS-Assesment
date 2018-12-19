#version 450 core
#extension GL_ARB_bindless_texture : enable

layout (location = 0) out vec4 rPosition;
layout (location = 1) out vec3 rNormal;
layout (location = 2) out vec4 rColor;

layout(std140, binding = 0) uniform MaterialBuffer
{
  vec4 color;
  sampler2D textureId;
};

uniform sampler2D texture10;

in vec4 out_position;
in vec3 out_normal;
in vec2 out_uv;

void main(void)
{
  rPosition = out_position;
  rNormal = out_normal;
  rColor = texture(textureId, out_uv) + color;
}
