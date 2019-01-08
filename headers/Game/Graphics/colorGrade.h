#ifndef COLORGRADE__
#define COLORGRADE__

#include "System/Graphics/Resources/postProcces.h"
#include "System/Graphics/Resources/texture.h"

class ColorGrade : public PostProcces
{
private:
  Texture * tex;
public:
  ColorGrade(Texture * lut, int w, int h, int sw, int sh, ShaderManager * shaderManager, GeometryLib * geometryLib);
  ~ColorGrade();
  void setTexture(Texture * tex);
  void setUniforms();
};
#endif