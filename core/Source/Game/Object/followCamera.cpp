#include "Game/Object/followCamera.h"

FollowCamera::FollowCamera(Vec3<float> * target, Object * object, Vec3<float> offset, Vec3<float> rot) : Camera(object)
{
  posPointer = target;
  this->offset = offset;
  rotation = rot;
}

FollowCamera::~FollowCamera()
{

}

Matrix<float> & FollowCamera::getMatrix()
{
  matrix.setAxisrotation(-rotation[0], X);
  other.setAxisrotation(-rotation[1], Y);
  matrix = matrix.multiplyByMatrix(other);
  camera.translateMatrix(-*posPointer - offset);
  camera = matrix.multiplyByMatrix(camera);
  // camera.lookAt((*posPointer) - offset, *posPointer, Vec3<float>(0, 1, 0));
  return camera;
}