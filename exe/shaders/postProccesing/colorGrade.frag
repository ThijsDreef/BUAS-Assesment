#version 450 core
#define ROWS 8.0
#define COLS 8.0
#define WIDTH 512.0
#define HEIGHT 512.0

layout(location = 0) out vec4 out_color;

uniform sampler2D texture10;
uniform sampler2D texture11;

in vec2 out_uv;

vec4 lookup(in vec4 textureColor, in sampler2D lookupTable) {
    textureColor = clamp(textureColor, 0.0, 1.0);

    float blueColor = textureColor.b * 63.0;

    vec2 colorId;
    colorId.y = floor(floor(blueColor) / 8.0);
    colorId.x = floor(blueColor) - (colorId.y * 8.0);

    vec2 colorUv;
    colorUv.x = (colorId.x * 1 / ROWS) + 0.5/WIDTH + (1 / ROWS - 1.0/WIDTH) * textureColor.r;
    colorUv.y = (colorId.y * 1 / COLS) + 0.5/HEIGHT + (1 / COLS - 1.0/HEIGHT) * textureColor.g;

    return texture(lookupTable, colorUv);;
}

void main()
{
    out_color = lookup(texture(texture10, out_uv), texture11);
}