#include "System/Physics/collisionComponent.h"

CollisionComponent::CollisionComponent(bool isStatic, Collider * collider, Transform * t, Object * object) : Component(object)
{
  moveAble = isStatic;
  coll = collider;
  transform = t;
  if (transform)
    coll->syncPos(&transform->getPos());
}

CollisionComponent::~CollisionComponent()
{

}

void CollisionComponent::update()
{

}

bool CollisionComponent::getStatic()
{
  return moveAble;
}

Collider * CollisionComponent::getCollider()
{
  return coll;
}