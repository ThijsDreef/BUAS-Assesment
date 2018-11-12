#ifndef MATERIAL__
#define MATERIAL__
#include "Math/vec4.h"
struct Material
{
  Vec4<float> color;
  unsigned int texture;
  char chars[235];

  Material(const Vec4<float>& color)
  {
    this->color = color;
  }
  Material()
  {
    color = Vec4<float>(1, 1, 1, 1);
  }
};

#endif
