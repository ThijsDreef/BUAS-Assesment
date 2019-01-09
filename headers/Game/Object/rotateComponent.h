#ifndef ROTATECOMPONENT__
#define ROTATECOMPONENT__

#include "System/Engine/EngineObjects/component.h"
#include "util/ease.h"
#include "Math/vec3.h"

class RotateComponent : public Component
{
private:
  double & dt;
  Vec3<float> & rotation;
  Vec3<float> toAdd;
  double passedTime = 0;
public:
  RotateComponent(Vec3<float> & rot, Vec3<float> toAddRotation, double & deltaTime, Object * object);
  virtual ~RotateComponent();
  void update();
};

#endif