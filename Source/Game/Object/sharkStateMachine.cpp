#include "Game/Object/sharkStateMachine.h"

float SharkStateMachine::interpolateEulerAngle(int from, int to, float speed)
{
  return ((to - from + 540)% 360 - 180) * speed; 
}

SharkStateMachine::SharkStateMachine(double & deltaTime, Object * object) : Component(object), dt(deltaTime)
{
  sharkTransform = object->getComponent<Transform>();
  originalFromJump = sharkTransform->getPos();
  state = CIRCLE;
}

SharkStateMachine::~SharkStateMachine()
{

}

void SharkStateMachine::lookAt(Vec3<float> to, float speed)
{
  Vec3<float> & rotation = sharkTransform->getRot();
  Vec3<float> toRotation = getLookAtRotation(sharkTransform->getPos(), to);
  rotation = toRotation;
  for (int i = 0; i < 3; i++) {
    rotation[i] += interpolateEulerAngle(rotation[i], toRotation[2 - i], dt * 0.33);
  }
}

Vec3<float> SharkStateMachine::getLookAtRotation(Vec3<float> from, Vec3<float> to)
{
  Vec3<float> rotation;
  //calculate angle on the y/x plane based this on trial and error
  rotation[0] = atan2f(from[1] - to[1], std::fabs(from[0] - to[0]));
  //calculate angle on the x/z plane
  rotation[1] = -atan2f(from[0] - to[0], from[2] - to[2]);
  // we dont want any roll so keep this zero
  rotation[2] = 0;
  return rotation * 180 / M_PI; 
}


void SharkStateMachine::chase()
{
  lookAt(*chaseTarget, dt * 0.33);
  Matrix<float> rot;
  rot = rot.rotation(sharkTransform->getRot());
  sharkTransform->getPos() += rot.multiplyByVector(Vec3<float>(0, 0, -10)) * dt;
}

void SharkStateMachine::circle()
{
  Matrix<float> rotation;
  rotation = rotation.rotation(sharkTransform->getRot());
  sharkTransform->getPos() += rotation.multiplyByVector(Vec3<float>(0, 0, -10)) * dt;
  sharkTransform->getRot() += Vec3<float>(0, 120, 0) * dt;
}

void SharkStateMachine::moveTo()
{
  lookAt(target, dt);
  Matrix<float> rot;
  rot = rot.rotation(sharkTransform->getRot());
  sharkTransform->getPos() += rot.multiplyByVector(Vec3<float>(0, 0, -10)) * dt;
  Vec3<float> distance = sharkTransform->getPos() - target;
  if (distance.length() < 0.2) 
  {
    state = CIRCLE;
    //compensate for x rotation changed during this state
    sharkTransform->getRot()[0] = 0;
    object->sendMessage("CIRCLE", &sharkTransform->getPos());
  }
}

void SharkStateMachine::jumpTo()
{ 
  passedTime += dt;
  float easeTime = Ease::cubicEaseInOut(passedTime * jumpTime);
  Vec3<float> nextJumpPlace;
  nextJumpPlace = originalFromJump * (1.0 - easeTime) + target * (easeTime);
  nextJumpPlace[1] = sinf(easeTime * M_PI) * jumpHeight + swimHeight;
  lookAt(nextJumpPlace, dt); 
  sharkTransform->getPos() = nextJumpPlace;
  Vec3<float> distance = sharkTransform->getPos() - target;
  if (distance.length() < 0.5) 
  {
    state = CIRCLE;
    //compensate for x rotation changed during this state
    sharkTransform->getRot()[0] = 0;
    object->sendMessage("CIRCLE", &sharkTransform->getPos());
  }
}

void SharkStateMachine::update()
{
  switch(state)
  {
    case CIRCLE:
      circle();
      break;
    case MOVETO:
      moveTo();
      break;
    case JUMPTO:
      jumpTo();
      break;
    case CHASE:
      chase();
      break;
  }
}

void SharkStateMachine::receiveMessage(const std::string & message, void* data)
{
  if (message == "JUMPTO") {
    jumpTo(*static_cast<Vec3<float>*>(data));
  } else if (message == "CIRCLE") {
    state = CIRCLE;
  } else if (message == "CHASE") {
    setChase(static_cast<Vec3<float>*>(data));
  } else if (message == "MOVETO") {
    target = *static_cast<Vec3<float>*>(data);
    state = MOVETO;
  }
}

void SharkStateMachine::setChase(Vec3<float> * toChase)
{
  chaseTarget = toChase;
  state = CHASE;
}

void SharkStateMachine::jumpTo(Vec3<float> jumpTarget)
{
  target = jumpTarget;
  originalFromJump = sharkTransform->getPos();
  state = JUMPTO;
}

void SharkStateMachine::setJumpTime(float time)
{
  jumpTime = 1/time;
}

Vec3<float> & SharkStateMachine::getOriginalFromJump()
{
  return originalFromJump;
}

Vec3<float> & SharkStateMachine::getTarget()
{
  return target;
}

void SharkStateMachine::setMoveScale(float * scale)
{
  moveScale = scale;
}