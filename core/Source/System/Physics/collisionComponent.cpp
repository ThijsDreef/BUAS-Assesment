#include "System/Physics/collisionComponent.h"

CollisionComponent::CollisionComponent(bool isStatic, Collider * collider, Transform * t, Object * object, std::string tag) : Component(object)
{
  coll = collider;
  coll->isStatic = isStatic;
  if (isStatic) {
    coll->isMoveAble = false;
  }
  transform = t;
  coll->setCollisionComponent(this);
  coll->tag = tag;
  if (transform)
    coll->syncPos(&transform->getPos());
}

CollisionComponent::~CollisionComponent()
{
  delete coll;
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