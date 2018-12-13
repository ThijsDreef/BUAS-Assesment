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
  frameForce = Vec3<float>();
  switch (currentState) {
    case DEFAULT:
      defaultState();
      break;
    case AIRTIME:
      airTimeState();
      break;
    case PIROUETTE:
      pirouetteState();
      break;
    case SPEEDING:
      speedingState();
      break;
    default:
      break;
  }
  rotationMatrix = rotationMatrix.rotation(*rotPointer);
  force += rotationMatrix.multiplyByVector(frameForce);
  *posPointer += force * dt;
}

PlayerMoveStateMachine::~PlayerMoveStateMachine()
{

}


void PlayerMoveStateMachine::airTimeState()
{

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
  frameForce[2] -= 1.25f;
  if (input->getKeyDown(16)) {
    currentState = SPEEDING;
    trickObject->setTrick("SPEEDING");
    rotationComponent->setDisabled();

  }

  if (input->getKeyDown(32) && grounded) {
    currentState = AIRTIME;
    trickObject->setTrick("AIRTIME");
    rotationComponent->setDisabled();
    frameForce[1] += 40;
  }
  
  if (input->getKeyDown(68) || input->getKeyDown(65)) {
    frameForce += Vec3<float>((input->getKeyDown(68) && std::abs((int)(*rotPointer)[1]) % 360 < 180) ? 20.0f : -20.0f, 0, 0);
    passedTime = 0;
    rotationComponent->setDisabled();
    trickObject->setTrick("PIROUETTE");
    currentState = PIROUETTE;

  }

  frameForce[1] -= 1.25;
  force -= force * dt * 3.25f;

  grounded = false;
}

void PlayerMoveStateMachine::speedingState()
{
  if (!input->getKeyDown(16)) {
    currentState = DEFAULT;
    rotationComponent->setEnabled();
    trickObject->clearTrick();
  }
  trickObject->addToScore(2);
  frameForce[2] -= 2.f;
  force -= force * dt * 3.25f;

}

void PlayerMoveStateMachine::pirouetteState()
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
  force -= force * dt * 0.5f;

  
}

void PlayerMoveStateMachine::receiveMessage(const std::string & name, void* data)
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