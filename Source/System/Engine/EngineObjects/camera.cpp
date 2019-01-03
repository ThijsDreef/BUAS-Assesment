#include "System/Engine/EngineObjects/camera.h"

Camera::Camera(Object * object) : Component(object)
{
  
}

Camera::~Camera()
{

}

Matrix<float> & Camera::getMatrix()
{
  return camera;
}

Vec3<float> & Camera::getPosition()
{
  return position;
}