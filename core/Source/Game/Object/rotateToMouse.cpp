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
  float dx = input->getNx();
  float dy = input->getNy();

  // dx -= 0.5;
  // dy -= 0.5;

  // dx *= 2;
  // dy *= 2;

  dy = -dy;

  float length = sqrtf(dx * dx + dy * dy);
  dy /= length;

  float angle = acosf(dy) * 180 / M_PI;
  
  (*rotation)[1] = ((dx > 0) ? angle : -angle) + 45;
}