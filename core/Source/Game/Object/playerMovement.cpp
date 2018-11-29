#include "Game/Object/playerMovement.h"

PlayerMovement::PlayerMovement(Vec3<float> * targetPosition, Vec3<float> * targetRotation, Input * input, Object * object) : Component(object)
{
  this->input = input;
  posPointer = targetPosition;
  rotPointer = targetRotation;
  object->subscribe("collision", this);
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

  if (input->getKeyDown(32) && grounded) 
    frameForce[1] += 0.65;

  frameForce[1] -= 0.025;
  Matrix<float> rotationMatrix;
  rotationMatrix = rotationMatrix.rotation(*rotPointer);

  frameForce = rotationMatrix.multiplyByVector(frameForce);

  force += frameForce;

  force *= 0.95;
  *posPointer += force;
  grounded = false;

}

PlayerMovement::~PlayerMovement()
{

}

void PlayerMovement::receiveMessage(const std::string & name, void* data)
{
  if (name == "collision") {
    Collider * coll = (Collider*)data;
    if (coll->tag == "ground") {
      grounded = true;
      force[1] = 0;
    }
  }
}