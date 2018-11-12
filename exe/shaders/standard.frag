#version 430 core
layout (location = 0) out vec4 out_color;
layout (std140,binding = 0) uniform materialBuffer
{
  vec4 color;
};
in vec3 out_normal;
in vec4 eye;
float ambient = 0.4;

vec4 getExposure(vec3 eye, vec3 normal, vec3 ldir, vec4 color)
{
  vec4 spec = vec4(0);
  vec3 e = vec3(normalize(eye));
  vec3 n = normalize(normal);
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
  out_color = vec4(0);
  out_color += getExposure(eye.xyz, out_normal, vec3(0, 0.5, 1.0), color);
}
