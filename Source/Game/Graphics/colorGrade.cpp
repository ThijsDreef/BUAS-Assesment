#include "Game/Graphics/colorGrade.h"

ColorGrade::ColorGrade(Texture * lut, int w, int h, int sw, int sh, ShaderManager * shaderManager, GeometryLib * geometryLib) : PostProcces(w, h, sw, sh, "colorGrade", shaderManager, geometryLib)
{
  tex = lut;
}

ColorGrade::~ColorGrade()
{

}

void ColorGrade::setUniforms()
{
  tex->bind(11);
}

void ColorGrade::setTexture(Texture * texture)
{
  tex = texture;
}