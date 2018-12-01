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
  trickObject->addToScore(1);

  force += frameForce;
  if (grounded) {
    trickObject->clearTrick();
    currentState = DEFAULT;
    rotationComponent->setEnabled();
  }
  // add points here for airtime
  // update score Text here
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
    frameForce[1] += 10.5 + std::abs(force[0] + force[2]);
  }

  frameForce[1] -= 1.25;
  Matrix<float> rotationMatrix;
  rotationMatrix = rotationMatrix.rotation(*rotPointer);

  frameForce = rotationMatrix.multiplyByVector(frameForce);

  force += frameForce;

  force *= 0.95;

  grounded = false;
}

void PlayerMoveStateMachine::speedingState()
{

}

void PlayerMoveStateMachine::pirouteState()
{
  // add a full rotation here

}
