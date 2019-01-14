#include "Game/Object/sharkStateMachine.h"

SharkStateMachine::SharkStateMachine(double & deltaTime, Object * object) : Component(object), dt(deltaTime)
{
  sharkTransform = object->getComponent<Transform>();
  state = MOVETO;
}

SharkStateMachine::~SharkStateMachine()
{

}

Vec3<float> getLookAtRotation(Vec3<float> from, Vec3<float> to)
{

  Vec3<float> look = from - to;
  look = look.normalize();
  Vec3<float> rotation;
  rotation[0] = -atan2f(look[2], look[1]);
  rotation[1] = -atan2f(look[0] * cosf(rotation[0]), look[2]);
  rotation[2] = 0;
  return rotation * 180 / M_PI; 
}

float interpolateEulerAngle(int from, int to, float speed)
{
  return ((to - from + 540)% 360 - 180) * speed; 
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
  Vec3<float> & rotation = sharkTransform->getRot();
  Vec3<float> toRotation = getLookAtRotation(sharkTransform->getPos(), target);
  rotation = toRotation;
  for (int i = 0; i < 3; i++) {
    rotation[i] += interpolateEulerAngle(rotation[i], toRotation[2 - i], dt * 3);
  }
  
  Matrix<float> rot;
  rot = rot.rotation(rotation);
  sharkTransform->getPos() += rot.multiplyByVector(Vec3<float>(0, 0, -10)) * dt;
  Vec3<float> distance = sharkTransform->getPos() - target;
  if (distance.length() < 0.2) state = CIRCLE;
}

void SharkStateMachine::jumpTo()
{

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
  }
}

void SharkStateMachine::receiveMessage(const std::string & message, void* data)
{

}