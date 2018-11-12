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
    while (collisions[i].hit->intersectB(collisions[i].other)) {
      Vec3<float> resolve = collisions[i].other->intersectA(collisions[i].hit);
      collisions[i].other->getPos() += resolve;
    }
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
    if (comp->getStatic())
      staticColliders.push_back(comp);
    else
      dynamicColliders.push_back(comp);
  }

}

CollisionModule::~CollisionModule()
{

}