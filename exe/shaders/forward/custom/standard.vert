#version 450 core
#define OFFSET 0.2
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

out vec2 out_uv;
out vec3 out_normal;
out vec4 eye;
out vec4 out_pos;

uniform float uTime;

float random (in vec2 st) {
    return fract(sin(dot(st.xy,vec2(12.9898,78.233)))*43758.5453123);
}


float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    vec2 u = f * f * (3.0 - 2.0 * f);

    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}

float bump(vec3 pos) {
    return noise((pos.xz - uTime) / 2) * noise((pos.xz + uTime) / 2) * 0.5;
}
vec3 filterNormal() 
{ 
    vec4 h; 
    h.x = bump(in_position + OFFSET * vec3( 0, 0, -1)); 
    h.y = bump(in_position + OFFSET * vec3(-1, 0, 0)); 
    h.z = bump(in_position + OFFSET * vec3( 1, 0, 0)); 
    h.w = bump(in_position + OFFSET * vec3( 0, 0, 1)); 
    vec3 n; 
    n.z = h.x - h.z; 
    n.x = h.y - h.w; 
    n.y = 2.; 
    return normalize(n); 
} 

void main()
{ 
  vec3 e = vec3(OFFSET, 0, 0);
  out_normal = normalize(vec3(bump(in_position - e) - bump(in_position + e), e.x, bump(in_position - e.zyx) - bump(in_position + e.zyx)));
  vec3 transPos = in_position + vec3(0, bump(in_position), 0);
  out_uv = in_uv;
  // out_normal = mat3(normal) * filterNormal();
  out_pos = model * vec4(transPos, 1);
  eye = (modelView * vec4(transPos, 1));
  gl_Position = mvp * vec4(transPos, 1);
}
