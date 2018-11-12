#ifndef ROTATETRANSFORM__
#define ROTATETRANSFORM__
#include "System/Engine/EngineObjects/transform.h"
#include "System/Input/input.h"
#include "System/Engine/EngineObjects/orbitalCamera.h"
#include "System/Engine/EngineObjects/object.h"
class RotateTransform : public Transform
{
private:
  Vec3<float> rotationSpeed;
  int lastX, lastY;
  Input * input;
public:
  Vec3<float> rotation;
  RotateTransform (Vec3<float> pos, Vec3<float> scale, Vec3<float> rot, std::string model, std::vector<std::string> materials, Input * input, Object * object);
  void update();
  virtual ~RotateTransform ();
};
#endif
