#ifndef ROTATETOMOUSE__
#define ROTATETOMOUSE__

#include "System/Input/input.h"
#include "System/Engine/EngineObjects/component.h"
#include "Math/vec3.h"
#include "Math/matrix.h"
#include "Math/vec2.h"

class RotateToMouse : public Component
{
private:
  Input * input;
  Vec3<float> * rotation;
  bool disabled = false;
public:
  RotateToMouse(Vec3<float> * target, Input * input, Object * objecct);
  virtual ~RotateToMouse();
  void update();
  void setEnabled();
  void setDisabled();
};

#endif