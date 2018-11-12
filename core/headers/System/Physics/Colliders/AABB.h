#ifndef AABB__
#define AABB__
#include "System/Physics/Colliders/collider.h"
#include <cmath>

class AABB : public Collider {
private:
  Vec3<float> r;
public:
  AABB(Vec3<float> pos, Vec3<float> radius);
  AABB();
  Vec3<float> intersectA(Collider * other);
  bool intersectB(Collider * other);
  Vec3<float> getRadius();
  void setRadius(Vec3<float> rad);
  virtual ~AABB ();
};

#endif
