#include "Game/Object/playerMovementStateMachine.h"

PlayerMoveStateMachine::PlayerMoveStateMachine(Vec3<float> * targetPosition, Vec3<float> * targetRotation, Input * input, Trick * trick, double & deltaTime, Object * object) : Component(object), dt(deltaTime)
{
  this->input = input;
  trickObject = trick;
  posPointer = targetPosition;
  rotPointer = targetRotation;
  rotationComponent = object->getComponent<RotateToMouse>();
  object->subscribe("collision", this);
}

void PlayerMoveStateMachine::update()
{
  switch (currentState) {
    case DEFAULT:
      defaultState();
      break;
    case AIRTIME:
      airTimeState();
      break;
    case PIROUTE:
      pirouteState();
      break;
    case SPEEDING:
      speedingState();
      break;
    default:
      break;
  }
  *posPointer += force * dt;
}

PlayerMoveStateMachine::~PlayerMoveStateMachine()
{

}

void PlayerMoveStateMachine::receiveMessage(const std::string & name, void* data)
{
  if (name == "collision") {
    Collider * coll = (Collider*)data;
    if (coll->tag == "ground") {
      grounded = true;
      force[1] = 0;
    }
  }
}

void PlayerMoveStateMachine::airTimeState()
{
  Vec3<float> frameForce;

  frameForce[1] -= 1.25;
  Matrix<float> rotationMatrix;

  rotationMatrix = rotationMatrix.rotation(*rotPointer);
  frameForce = rotationMatrix.multiplyByVector(frameForce);

  force += frameForce;
  if (grounded) {
    trickObject->clearTrick();
    rotationComponent->setEnabled();
    currentState = DEFAULT;
  }
  // add points here for airtime
  trickObject->addToScore(std::abs(force[1]));
}

void PlayerMoveStateMachine::defaultState()
{
  Vec3<float> frameForce;

  if (input->getKeyDown(87)) {
    frameForce[2] -= 1.5f;
  }

  if (input->getKeyDown(32) && grounded) {
    currentState = AIRTIME;
    trickObject->setTrick("AIRTIME");
    rotationComponent->setDisabled();
    frameForce[1] += 35;
  }
  if (input->getKeyDown(68) || input->getKeyDown(65)) {
    force[0] += (input->getKeyDown(68)) ? 25.0f : -25.0f;
    passedTime = 0;
    rotationComponent->setDisabled();
    trickObject->setTrick("PIROUTE");
    currentState = PIROUTE;

  }

  frameForce[1] -= 1.25;
  Matrix<float> rotationMatrix;
  rotationMatrix = rotationMatrix.rotation(*rotPointer);

  frameForce = rotationMatrix.multiplyByVector(frameForce);

  force += frameForce;

  force -= force * dt * 3.25f;

  grounded = false;
}

void PlayerMoveStateMachine::speedingState()
{

}

void PlayerMoveStateMachine::pirouteState()
{
  // add a full rotation here
  passedTime += dt;
  (*rotPointer)[1] += 360 * dt;
  if (passedTime >= 1.0) {
    trickObject->clearTrick();
    rotationComponent->setEnabled();
    currentState = DEFAULT;
  }
  trickObject->addToScore(20);
  force -= force * dt * 2.25f;

  
}
