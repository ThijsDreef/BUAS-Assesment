#ifndef FOLOWCAMERA__
#define FOLOWCAMERA__

#include "System/Engine/EngineObjects/camera.h"

class FollowCamera : public Camera 
{
private:
  Vec3<float> * posPointer;
  Vec3<float> offset;
  Vec3<float> rotation;
  Vec3<float> lock;
  Matrix<float> matrix;
  Matrix<float> other;
public:
  FollowCamera(Vec3<float> * target, Object * object, Vec3<float> offset = Vec3<float>(0, 0, 2), Vec3<float> rot = Vec3<float>(), Vec3<float> locked = Vec3<float>(1, 1, 1));
  virtual ~FollowCamera();
  Matrix<float> & getMatrix();
  Vec3<float> & getPosition();
};

#endif