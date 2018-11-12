#ifndef OCTREE__
#define OCTREE__
#include "System/Physics/Colliders/AABB.h"
#include "System/Physics/bucket.h"

struct Collision {
  Collider* hit;
  Collider* other;
  Collision(Collider * h, Collider* o)
  {
    hit = h;
    other = o;
  }
};

class Octree {
private:
  Bucket * root;
  AABB space;
  std::vector<Collision> collisions;

  std::vector<Bucket*> allBuckets;
  Bucket * getLowestBucket(Collider * coll);
  Bucket * getLowerBucket(Bucket * b, Collider * coll);
  void checkBucketCollision(Bucket * b, std::vector<Collision> & collisions);
  void checkPair(std::vector<Collision> & collisions, std::vector<Collider*> & staticNodes, std::vector<Collider*> & dynamicNodes);
  void checkDynamic(std::vector<Collision> & collisions, std::vector<Collider*> & dynamicNodes);
public:
  Octree (AABB size, int layers);
  virtual ~Octree ();
  bool addStaticCollider(Collider * coll);
  bool addDynamicCollider(Collider * coll);
  std::vector<Collision> & getCollisions();
  void cleanDynamic();
  // std::vector<Collision> & queryTreeCollider(Collider * col);
  // std::vector<Collision> & querTreeLine(Vec3<float> start, Vec3<float> end, Vec3<float> tolerance);
};

#endif
