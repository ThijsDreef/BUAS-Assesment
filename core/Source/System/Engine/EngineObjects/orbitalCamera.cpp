#include "System/Engine/EngineObjects/orbitalCamera.h"

OrbitalCamera::OrbitalCamera(float offset, Vec3<bool> locked, Vec3<float> camRot, Vec3<float> * rotation, Vec3<float> * pos, bool interpolated, Object * object) : Camera(object)
{
  this->interpolated = interpolated;
  this->offset = offset;
  this->locked = locked;
  rot = camRot;
  rotPoint = rotation;
  posPoint = pos;
}

OrbitalCamera::~OrbitalCamera()
{

}

void OrbitalCamera::update()
{
  //translate away from origin to rotate around a point
  camera.translateMatrix(Vec3<float>(0, 0, offset));
  //if interpolated == true lerp the interpolrot and use that instead of locked/normal rot
  interpolRot = lerp(interpolRot, *rotPoint, 0.1);
  //todo fix this with operater makes a vector negative
  Vec3<float> negativeIntePolRot = -interpolRot;
  if (locked[0])
    matrix.setAxisrotation(rot[0], X);
  else if (interpolated)
      matrix.setAxisrotation(negativeIntePolRot[0] + rot[0], X);
  else
    matrix.setAxisrotation(-(*rotPoint)[0] + rot[0], X);
  camera = camera.multiplyByMatrix(matrix);
  if (locked[2])
    matrix.setAxisrotation(rot[2], Z);
  else if (interpolated)
    matrix.setAxisrotation(negativeIntePolRot[2] + rot[2], Z);
  else
    matrix.setAxisrotation(-(*rotPoint)[2] + rot[2], Z);
  camera = camera.multiplyByMatrix(matrix);
  if (locked[1])
    matrix.setAxisrotation(rot[1], Y);
  else if (interpolated)
    matrix.setAxisrotation(negativeIntePolRot[1] + rot[1], Y);
  else
    matrix.setAxisrotation(-(*rotPoint)[1] + rot[1], Y);
  camera = camera.multiplyByMatrix(matrix);
  matrix.translateMatrix(-(*posPoint));
  camera = camera.multiplyByMatrix(matrix);
}

Matrix<float> & OrbitalCamera::getMatrix()
{
  return camera;
}

Vec3<float> OrbitalCamera::lerp(Vec3<float> current, Vec3<float> target, float speed)
{
  return current + speed * (target - current);
}

float * OrbitalCamera::getOffset()
{
  return &offset;
}
