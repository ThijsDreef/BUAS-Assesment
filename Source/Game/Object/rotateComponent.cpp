#include "Game/Object/rotateComponent.h"

RotateComponent::RotateComponent(Vec3<float> & rot, Vec3<float> toAddRotation, double & deltaTime, Object * object) : dt(deltaTime), rotation(rot), Component(object)
{
  toAdd = toAddRotation;
}

RotateComponent::~RotateComponent()
{
    
}

void RotateComponent::update()
{
  passedTime += dt * 0.5;
  rotation = (rotation * (Vec3<float>(1, 1, 1) - toAdd.sign().abs())) + toAdd.sign().abs() * toAdd * Ease::quintEaseInOut(passedTime - (int)passedTime);
}
