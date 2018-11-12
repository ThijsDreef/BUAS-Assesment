#include "Game/Object/playerMovement.h"

PlayerMovement::PlayerMovement(Vec3<float> * target, Input * input, Object * object) : Component(object)
{
  this->input = input;
  posPointer = target;
}

void PlayerMovement::update()
{
  if (input->getKeyDown(87)) {
    force[2] -= 0.02f;
  } else if (input->getKeyDown(83)) {
    force[2] += 0.02f;
  }

  if (input->getKeyDown(65)) {
    force[0] -= 0.02f;    
  } else if (input->getKeyDown(68)) {
    force[0] += 0.02f;
  }

  force *= 0.95;
  *posPointer += force;
}

PlayerMovement::~PlayerMovement()
{

}