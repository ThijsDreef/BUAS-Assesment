#include "Game/Object/playerMovement.h"

PlayerMovement::PlayerMovement(Vec3<float> * targetPosition, Vec3<float> * targetRotation, Input * input, double & deltaTime, Object * object) : Component(object), dt(deltaTime)
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
    frameForce[2] -= 2;
  } else if (input->getKeyDown(83)) {
    frameForce[2] += 2;
  }

  if (input->getKeyDown(65)) {
    frameForce[0] -= 2;    
  } else if (input->getKeyDown(68)) {
    frameForce[0] += 2;
  }
 
  if (input->getKeyDown(32) && grounded) {
    frameForce[1] += 55;
    boosted = false;
  }
  if (input->getKeyDown(16) && !boosted) {
    boosted = true;
    force[0] *= 1.5;
    force[1] += 20;
  }

  frameForce[1] -= 2;
  Matrix<float> rotationMatrix;
  rotationMatrix = rotationMatrix.rotation(*rotPointer);

  frameForce = rotationMatrix.multiplyByVector(frameForce);

  force += frameForce;

  force.lerp(Vec3<float>(0, 0, 0), 1 - powf(0.05, dt));
  
  *posPointer += force * dt;
  grounded = false;

}

PlayerMovement::~PlayerMovement()
{

}

void PlayerMovement::receiveMessage(const std::string & name, void* data)
{
  if (name == "collision") {
    CollisionData * coll = static_cast<CollisionData*>(data);
    if (coll->other->tag == "ground") {
      if (coll->firstResolution[1] != 0) {
        grounded = true;
        force[1] = 0;
      }
    }
  }
}