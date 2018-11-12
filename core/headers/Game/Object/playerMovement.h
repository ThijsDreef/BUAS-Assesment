#ifndef PLAYERMOVEMENT__
#define PLAYERMOVEMENT__

#include "System/Engine/EngineObjects/component.h"
#include "Math/vec3.h"
#include "System/Input/input.h"

class PlayerMovement : public Component
{
private:
  Input * input;
  Vec3<float> * posPointer;
  Vec3<float> force;
public:
  PlayerMovement(Vec3<float> * target, Input * input, Object * object);
  virtual ~PlayerMovement();
  void update();
};
#endif