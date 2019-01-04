#include "Game/Object/playerMovement.h"

PlayerMovement::PlayerMovement(Vec3<float> * targetPosition, Vec3<float> * targetRotation, Input * input, double & deltaTime, Object * object) : Component(object), dt(deltaTime)
{
  this->input = input;
  posPointer = targetPosition;
  rotPointer = targetRotation;
  object->subscribe("collision", this);
}

float PlayerMovement::getTargetAngle(Vec3<float> & frameForce)
{
  int targetAngle = -1;
  if (input->getKeyDown(87)) {
    frameForce[0] += 1.5;
    targetAngle = 0;
    if (input->getKeyDown(65)) {
      targetAngle = 315;
    }
    if (input->getKeyDown(68)) {
      targetAngle = 45;
    }
  } else if (input->getKeyDown(83)) {
    frameForce[0] += 1.5;
    targetAngle = 180;
    if (input->getKeyDown(65)) {
      targetAngle = 225;
    }
    if (input->getKeyDown(68)) {
      targetAngle = 135;
    }
  } else if (input->getKeyDown(65)) {
    frameForce[0] += 1.5;
    targetAngle = 270;
  } else if (input->getKeyDown(68)) {
    frameForce[0] += 1.5;
    targetAngle = 90;
  }

  return targetAngle;
}

void PlayerMovement::update()
{
  if (dt == 0) return;
  Vec3<float> frameForce;
  float targetAngle = getTargetAngle(frameForce);

  if (targetAngle != -1) {
    int delta = ((int)targetAngle - (int)(*rotPointer)[1] + 540) % 360 - 180;
    (*rotPointer)[1] += delta * 0.175;
  }

  if (input->getKeyDown(32) && grounded) {
    frameForce[1] += 55;
    force[1] = 0;
    boosted = false;
  } else if (input->getKeyDown(16) && !boosted && !grounded) {
    boosted = true;
    force[1] += 40;
  }

  frameForce[1] -= 2;

  Matrix<float> rotationMatrix;
  rotationMatrix = rotationMatrix.rotation(*rotPointer);

  frameForce = rotationMatrix.multiplyByVector(frameForce);

  force += frameForce;
  //semi correct way to slow based on passed time
  force.lerp(Vec3<float>(0, 0, 0), 1 - powf(0.1, dt));
  
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
      if (coll->firstResolution[1] < 0) {
        grounded = true;
        force[1] = -20;
      }
    }
  }
}