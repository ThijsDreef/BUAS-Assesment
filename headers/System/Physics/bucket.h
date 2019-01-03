#ifndef BUCKET__
#define BUCKET__

#include "System/Physics/Colliders/AABB.h"
#include <vector>

class Bucket {
private:
  Bucket * parent;
  std::vector<Bucket*> children;
  std::vector<Collider*> staticNodes;
  std::vector<Collider*> dynamicNodes;
  AABB bb;
public:
  Bucket (AABB aabb, Bucket * top, int recursiveCount);
  virtual ~Bucket ();
  void addStaticNode(Collider * aabb);
  void addDynamicNode(Collider * aabb);
  bool removeStaticNode(Collider * node);
  bool removeDynamicNode(Collider * node);
  bool queryInside(Collider * coll);
  std::vector<Bucket*> queryLowestBucket(Collider * coll);
  std::vector<Bucket*> & getChildren();
  std::vector<Collider*> & getStatic();
  std::vector<Collider*> & getDynamic();
  void cleanDynamic();
};

#endif
