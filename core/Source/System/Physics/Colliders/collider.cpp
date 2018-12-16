#include "System/Physics/Colliders/collider.h"

Collider::Collider()
{

}

Collider::~Collider()
{

}

void Collider::setScale(Vec3<float> s)
{
  scale = s;
}

bool Collider::intersectB(Collider * other)
{
  return false;
}

Vec3<float> Collider::intersectA(Collider * other)
{
  return Vec3<float>();
}

void Collider::setPos(Vec3<float> & pos)
{
  p = pos;
}

Vec3<float> & Collider::getPos()
{
  if (posPointer)
    return *posPointer;
  else
    return p;
}

void Collider::syncPos(Vec3<float> * pos)
{
  posPointer = pos;
}

void Collider::setCollisionComponent(CollisionComponent * component)
{
  collComponent = component;
}

CollisionComponent * Collider::getCollisionComponent()
{
  return collComponent;
}
