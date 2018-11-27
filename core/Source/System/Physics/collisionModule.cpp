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
    while (collisions[i].hit->intersectB(collisions[i].other) && tries < 200) {
      Vec3<float> resolve = collisions[i].other->intersectA(collisions[i].hit);
      if (!collisions[i].other->isStatic)
        collisions[i].other->getPos() += resolve;
      if (!collisions[i].hit->isStatic)
        collisions[i].hit->getPos() -= resolve;

      tries ++;
    }
    collisions[i].hit->getCollisionComponent()->getObject()->sendMessage("collision", &collisions[i].other);
    collisions[i].other->getCollisionComponent()->getObject()->sendMessage("collision", &collisions[i].hit);

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