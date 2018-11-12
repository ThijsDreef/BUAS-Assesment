#include "Game/Object/rotateTransform.h"

RotateTransform::RotateTransform(Vec3<float> pos, Vec3<float> scale, Vec3<float> rot, std::string model, std::vector<std::string> materials, Input * input, Object* object)
:
Transform(pos, scale, rot, model, materials, object)
{
  this->input = input;
  // input->setMouseLock(true);
  rotation = rot;
}

void RotateTransform::update()
{
  if (input->getMouseButtonDown(0))
  {
    rotationSpeed[0] = (input->getDy() / 3);
    rotationSpeed[1] = (input->getDx());
    lastX = input->getDx();
    lastY = input->getDy();
  }
  else
  {
    rotationSpeed[0] = 0;
    rotationSpeed[1] = 0;
  }
  rotation += rotationSpeed;
  rot[1] = rotation[1];
  rot[0] = rotation[0];
}

RotateTransform::~RotateTransform()
{

}
