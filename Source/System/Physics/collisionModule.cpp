#include "System/Physics/collisionModule.h"

CollisionModule::CollisionModule(int width, int octreeDepth) : octree(AABB(Vec3<float>(0, 0, 0), Vec3<float>(width, width, width)), octreeDepth)
{

}

void CollisionModule::update()
{
  for (unsigned int i = 0; i < dynamicColliders.size(); i++)
    octree.addDynamicCollider(dynamicColliders[i]->getCollider());
  std::vector<Collision> collisions = octree.getCollisions();
  // please handle collisions here
  for (unsigned int i = 0; i < collisions.size(); i++)
  {
    // reall dirty way to resolve collisions needs some better way eventually
    int tries = 0;

    Vec3<float> hit = collisions[i].other->intersectA(collisions[i].hit);
    Vec3<float> other = collisions[i].hit->intersectA(collisions[i].other);
    if (!(collisions[i].other->isTrigger || collisions[i].hit->isTrigger)) {
      while (collisions[i].hit->intersectB(collisions[i].other) && tries < 1000) {
        Vec3<float> otherResolve = collisions[i].other->intersectA(collisions[i].hit);
        Vec3<float> resolve = collisions[i].hit->intersectA(collisions[i].other);

        if (!collisions[i].other->isStatic && collisions[i].other->isMoveAble)
          collisions[i].other->getPos() += otherResolve;
        if (!collisions[i].hit->isStatic && collisions[i].hit->isMoveAble)
          collisions[i].hit->getPos() += resolve;

        tries ++;
      }
    }
    CollisionData data = CollisionData(collisions[i].other, hit);
    collisions[i].hit->getCollisionComponent()->getObject()->sendMessage("collision", &data);
    data = CollisionData(collisions[i].hit, other);
    collisions[i].other->getCollisionComponent()->getObject()->sendMessage("collision", &data);

  }
  // set debug count here
  collisionCount = collisions.size();
  octree.cleanDynamic();
}

void CollisionModule::addObject(Object * object)
{
  CollisionComponent * comp = object->getComponent<CollisionComponent>();
  if (comp)
  {
    if (comp->getStatic()) {
      staticColliders.push_back(comp);
      octree.addStaticCollider(comp->getCollider());
    }
    else
      dynamicColliders.push_back(comp);
  }

}

CollisionModule::~CollisionModule()
{

}