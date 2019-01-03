#ifndef ORBITALCAMERA__
#define ORBITALCAMERA__
#include "System/Engine/EngineObjects/camera.h"
#include "System/Engine/EngineObjects/transform.h"

class OrbitalCamera : public Camera
{
private:
  float offset;
  bool interpolated;
  Matrix<float> matrix;
  Vec3<bool> locked;
  Vec3<float> interpolRot;
  Vec3<float> rot;
  Vec3<float> * rotPoint;
  Vec3<float> * posPoint;
public:
  float * getOffset();
  OrbitalCamera (float offset, Vec3<bool> locked, Vec3<float>camRot,  Vec3<float> * rotation, Vec3<float> * pos, bool interpolated, Object * object);
  void update();
  virtual ~OrbitalCamera ();
  Matrix<float> & getMatrix();
  Vec3<float> lerp(Vec3<float> current, Vec3<float> target, float speed);
};
#endif
