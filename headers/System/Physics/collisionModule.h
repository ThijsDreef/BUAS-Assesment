#ifndef COLLISIONMODULE__
#define COLLISIONMODULE__


#include "System/module.h"
#include "System/Physics/octree.h"
#include "System/Engine/EngineObjects/object.h"
#include "System/Physics/collisionComponent.h"

struct CollisionData
{
  Collider * other;
  Vec3<float> firstResolution;
  CollisionData(Collider * o, Vec3<float> r)
  {
    other = o;
    firstResolution = r;
  }
};

class CollisionModule : public Module
{
private:
  Octree octree;
  std::vector<CollisionComponent*> staticColliders;
  std::vector<CollisionComponent*> dynamicColliders;
public:
  unsigned int collisionCount;
  CollisionModule(int width, int octreeDepth);
  virtual ~CollisionModule();
  void update();
  void addObject(Object * object);
};

#endif
