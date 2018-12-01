#include "Game/Object/followCamera.h"

FollowCamera::FollowCamera(Vec3<float> * target, Object * object, Vec3<float> offset, Vec3<float> rot, Vec3<float> locked) : Camera(object)
{
  posPointer = target;
  this->offset = offset;
  rotation = rot;
  lock = locked;
}

FollowCamera::~FollowCamera()
{

}

Vec3<float> & FollowCamera::getPosition()
{
  return *posPointer;
}

Matrix<float> & FollowCamera::getMatrix()
{
  matrix.setAxisrotation(-rotation[0], X);
  other.setAxisrotation(-rotation[1], Y);
  matrix = matrix.multiplyByMatrix(other);
  Vec3<float> pos = *posPointer * lock;
  camera.translateMatrix(-pos - offset);
  camera = matrix.multiplyByMatrix(camera);
  // camera.lookAt((*posPointer) - offset, *posPointer, Vec3<float>(0, 1, 0));
  return camera;
}