#version 450 core
#extension GL_ARB_bindless_texture : enable

layout (location = 0) out vec4 out_color;
layout (std140,binding = 0) uniform materialBuffer
{
  vec4 color;
  sampler2D textureId;
};

in vec4 out_pos;
in vec3 out_normal;
in vec4 eye;
in vec2 out_uv;

uniform float uTexScroll;

uniform sampler2D texture0;
uniform sampler2D texture10;

uniform vec3 directionalLight;
uniform mat4 uLightVP;


float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(texture0, projCoords.xy).r;
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float bias = 0.0010;
    // return currentDepth > texture(texture3, projCoords.xy + bias).r ? 1. : 0.0;
    float shadow = 0;

    if (projCoords.x > 1. || projCoords.x < 0. || projCoords.y > 1. || projCoords.y < 0.) return 0.;
    for (int x = -2; x <= 2; x++) {
      for (int y= -2; y <= 2; y++) {
        // shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
        shadow += currentDepth > texture(texture0, projCoords.xy + vec2(x * (1.0 / 8192), y * (1.0 / 8192))).r + bias ? 1.0 : 0.0;
      }
    }
    return (shadow / 16.) * 0.5;
}

vec4 getExposure(vec3 eye, vec3 normal, vec3 ldir, vec4 color)
{
  vec4 spec = vec4(0);
  vec3 e = vec3(normalize(eye));
  vec3 n = normalize(normal);
  ldir = normalize(ldir);
  float power = max(dot(n, ldir), 0.0);
  if (power > 0.0)
  {
    vec3 h = normalize(ldir + e);
    float intSpec = max(dot(h,n), 0.0);
    spec = vec4(0.5) * pow(intSpec, 5);
  }
  return color * min(power, 1);
}

void main(void)
{
  vec2 uv = out_uv;
  uv.y += uTexScroll;
  uv *= 4;
  out_color = texture(textureId, uv);
  out_color.xyz *= max(dot(out_normal, directionalLight), 0.);
  out_color *= vec4(1.0) - vec4(ShadowCalculation(uLightVP * out_pos, out_normal));
  out_color *= 0.8;
  out_color.w = 0.5;
}
