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

  
  float targetAngle = ((nx > 0) ? angle : -angle) + 45;
  float currentAngle = (*rotation)[1];

  //targetBearing - currentBearing + 540 (aka 360 for a full circle and 180 to get difference always from a full circle) % 360 to get back to "unit space" - 180 to normalize the 540 part
  int delta = ((int)targetAngle - (int)currentAngle + 540) % 360 - 180;
  //interpolate here please
  (*rotation)[1] += delta * 0.25f;
}

void RotateToMouse::setEnabled() 
{
  disabled = false;
}

void RotateToMouse::setDisabled()
{
  disabled = true;
}