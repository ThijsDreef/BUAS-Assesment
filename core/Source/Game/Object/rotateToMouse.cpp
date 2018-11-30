#include "Game/Object/rotateToMouse.h"


RotateToMouse::RotateToMouse(Vec3<float> * target, Input * input, Object * object) : Component(object)
{
  this->input = input;
  rotation = target;
}

RotateToMouse::~RotateToMouse()
{

}

void RotateToMouse::update()
{
  if (disabled)  return;
  float nx = input->getNx();
  float ny = input->getNy();

  ny = -ny;

  float length = sqrtf(nx * nx + ny * ny);
  ny /= length;
  
  float angle = acosf(ny) * 180 / M_PI;

  
  float targetAngle = ((nx > 0) ? angle : -angle);
  float currentAngle = (*rotation)[1];
  //interpolate here please
  (*rotation)[1] = targetAngle;
}

void RotateToMouse::setEnabled() 
{
  disabled = false;
}

void RotateToMouse::setDisabled()
{
  disabled = true;
}