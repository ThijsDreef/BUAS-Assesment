#include "System/Physics/collisionComponent.h"

CollisionComponent::CollisionComponent(bool isStatic, Collider * collider, Transform * t, Object * object) : Component(object)
{
  coll = collider;
  collider->isStatic = isStatic;
  transform = t;
  collider->setCollisionComponent(this);
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
  return coll->isStatic;
}

Collider * CollisionComponent::getCollider()
{
  return coll;
}