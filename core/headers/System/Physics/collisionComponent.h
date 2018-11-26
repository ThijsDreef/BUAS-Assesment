#ifndef COLLISIONCOMPONENT__
#define COLLISIONCOMPONENT__

#include "System/Physics/Colliders/collider.h"
#include "System/Engine/EngineObjects/transform.h"

class CollisionComponent : public Component
{
private:
  Collider * coll;
  Transform * transform;
public:
  CollisionComponent (bool isStatic, Collider * collider, Transform * transform, Object * object);
  Collider * getCollider();
  virtual ~CollisionComponent ();
  bool getStatic();
  void update();
};

#endif
