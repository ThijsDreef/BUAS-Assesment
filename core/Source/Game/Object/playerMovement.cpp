#include "Game/Object/playerMovement.h"

PlayerMovement::PlayerMovement(Vec3<float> * targetPosition, Vec3<float> * targetRotation, Input * input, Object * object) : Component(object)
{
  this->input = input;
  posPointer = targetPosition;
  rotPointer = targetRotation;
}

void PlayerMovement::update()
{
  
  Vec3<float> frameForce;

  if (input->getKeyDown(87)) {
    frameForce[2] -= 0.02f;
  } else if (input->getKeyDown(83)) {
    frameForce[2] += 0.02f;
  }

  if (input->getKeyDown(65)) {
    frameForce[0] -= 0.02f;    
  } else if (input->getKeyDown(68)) {
    frameForce[0] += 0.02f;
  }

  Matrix<float> rotationMatrix;
  rotationMatrix = rotationMatrix.rotation(*rotPointer);

  frameForce = rotationMatrix.multiplyByVector(frameForce);

  force += frameForce;

  force *= 0.95;

  *posPointer += force;
}

PlayerMovement::~PlayerMovement()
{

}