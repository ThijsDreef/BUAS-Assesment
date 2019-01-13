#include "Game/Object/sharkStateMachine.h"

SharkStateMachine::SharkStateMachine(double & deltaTime, Object * object) : Component(object), dt(deltaTime)
{
  sharkTransform = object->getComponent<Transform>();
  state = MOVETO;
}

SharkStateMachine::~SharkStateMachine()
{

}

float getAngle2DPlane(Vec3<float> from, Vec3<float> to, int component)
{
  Vec3<float> delta = from - to;
  delta = delta.normalize();
  int minusComponent = component - 1;
  minusComponent = (minusComponent < 0) ? 2 : minusComponent;
  float angle = acosf(delta[component]) * 180 * M_PI;
  return (delta[minusComponent] > 0) ? angle : -angle;
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
  for (int i = 0; i < 3; i++) {
    rotation[i] += interpolateEulerAngle(rotation[i], getAngle2DPlane(sharkTransform->getPos(), target, i), dt * 3);
  }
  Matrix<float> rot;
  rot = rot.rotation(rotation);
  sharkTransform->getPos() += rot.multiplyByVector(Vec3<float>(0, 0, -10)) * dt;
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