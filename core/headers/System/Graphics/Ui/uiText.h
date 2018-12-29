#ifndef UITEXT__
#define UITEXT__

#include "System/Engine/EngineObjects/component.h"
#include "System/Graphics/Resources/buffer.h"
#include <vector>
#include "System/Graphics/Ui/font.h"
#include "Math/vec2.h"
#include "Math/matrix.h"

struct TextGPUData
{
  Vec2<float> vertex;
  Vec2<float> uv;
  TextGPUData(Vec2<float> vert, Vec2<float> texCoord)
  {
    vertex = vert;
    uv = texCoord;
  }
};


class UIText : public Component
{
protected:
  std::string text;
  Vec2<float> pos;
  Matrix<float> mv;
  float scale = 1.f;
  float alpha = 1.f;
  float centerX = 0.0f;
private:
  bool dirty;
  std::vector<unsigned int> indices;
  Buffer fontBuffer;
  float inverseAspect;
public:
  bool shouldCenter = false;
  bool outLine = true;
  Matrix<float> & getMatrix();
  std::vector<unsigned int> & getIndices();
  void buildBuffer(Font * font, float inverseAspect);
  unsigned int getBuffer();
  void setPos(Vec2<float> position);
  Vec2<float> & getPos();
  void setClean();
  float getAlpha();
  void setScale(float s);
  float getScale();
  bool isDirty();
  void setText(std::string newText);
  std::string & getText();
  UIText(std::string startText, Vec2<float> position, Object * object);
  virtual ~UIText();
};

#endif