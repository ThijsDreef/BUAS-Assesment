#include "Game/Object/playerMovementStateMachine.h"

PlayerMoveStateMachine::PlayerMoveStateMachine(Vec3<float> * targetPosition, Vec3<float> * targetRotation, Input * input, double & deltaTime, Object * object) : Component(object), dt(deltaTime)
{
  this->input = input;
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
    currentState = DEFAULT;
    rotationComponent->setEnabled();

  }
}

void PlayerMoveStateMachine::defaultState()
{
  Vec3<float> frameForce;

  if (input->getKeyDown(87)) {
    frameForce[2] -= 2.0f;
  } else if (input->getKeyDown(83)) {
    frameForce[2] += 2.0f;
  }

  if (input->getKeyDown(65)) {
    frameForce[0] -= 2.0f;    
  } else if (input->getKeyDown(68)) {
    frameForce[0] += 2.0f;
  }

  if (input->getKeyDown(32) && grounded) {
    currentState = AIRTIME;
    rotationComponent->setDisabled();
    frameForce[1] += 28.5;
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

}
