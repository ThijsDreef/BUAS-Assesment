#ifndef FOLOWCAMERA__
#define FOLOWCAMERA__

#include "System/Engine/EngineObjects/camera.h"

class FollowCamera : public Camera 
{
private:
  Vec3<float> * posPointer;
  Vec3<float> offset;
  Vec3<float> rotation;
  Matrix<float> matrix;
  Matrix<float> other;
public:
  FollowCamera(Vec3<float> * target, Object * object, Vec3<float> offset = Vec3<float>(0, 0, 2), Vec3<float> rot = Vec3<float>());
  ~FollowCamera();
  Matrix<float> & getMatrix();
};

#endif