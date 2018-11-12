#include "System/Physics/octree.h"

Octree::Octree(AABB size, int layers)
{

  space = size;
  root = new Bucket(space, 0, layers);
  allBuckets.push_back(root);
  for (unsigned int i = 0; i < allBuckets.size(); i++)
  {
    std::vector<Bucket*> children = allBuckets[i]->getChildren();
    for (unsigned int j = 0; j < children.size(); j++)
    {
      allBuckets.push_back(children[j]);
    }
  }
}

Octree::~Octree()
{
  delete root;
}

Bucket * Octree::getLowestBucket(Collider * coll)
{
  Bucket * oldBucket = 0;
  Bucket * newBucket = root;
  while (oldBucket != newBucket)
  {
    oldBucket = newBucket;
    newBucket = getLowerBucket(oldBucket, coll);
  }
  return oldBucket;
}

Bucket * Octree::getLowerBucket(Bucket * b, Collider * coll)
{
  std::vector<Bucket*> buckets = b->queryLowestBucket(coll);
  if (buckets.size() > 1 || buckets.size() == 0) return b;
  else return buckets[0];
}

void Octree::checkBucketCollision(Bucket * b, std::vector<Collision> & collisions)
{
  std::vector<Collider*> staticNodes = b->getStatic();
  std::vector<Collider*> dynamicNodes = b->getDynamic();
  checkPair(collisions, staticNodes, dynamicNodes);
  checkDynamic(collisions, dynamicNodes);

  std::vector<Bucket*> children = b->getChildren();
  for (unsigned int i = 0; i < children.size(); i++)
  {
    std::vector<Collider*> childStaticNode = children[i]->getStatic();
    std::vector<Collider*> childDynamicNodes = children[i]->getDynamic();
    checkPair(collisions, dynamicNodes, childStaticNode);
    checkPair(collisions, dynamicNodes, childDynamicNodes);
  }

}

void Octree::checkPair(std::vector<Collision> & collisions, std::vector<Collider*> & staticNodes, std::vector<Collider*> & dynamicNodes)
{
  for (unsigned int j = 0; j < staticNodes.size(); j++)
  {
    for (unsigned int i = 0; i < dynamicNodes.size(); i++)
    {
      if (staticNodes[j]->intersectB(dynamicNodes[i])) {
        collisions.push_back(Collision(staticNodes[j], dynamicNodes[i]));
      }
    }
  }
}

void Octree::checkDynamic(std::vector<Collision> & collisions, std::vector<Collider*> & dynamicNodes)
{
  for (unsigned int i = 0; i < dynamicNodes.size(); i++)
  {
    for (unsigned int j = i + 1; j < dynamicNodes.size(); j++)
    {
      if (dynamicNodes[i]->intersectB(dynamicNodes[j]))
        collisions.push_back(Collision(dynamicNodes[i], dynamicNodes[j]));
    }
  }
}

bool Octree::addStaticCollider(Collider * coll)
{
    if (!coll->intersectB(&space)) return false;
    Bucket * b = getLowestBucket(coll);
    if (b != 0) b->addStaticNode(coll);
    else return false;
    return true;
}

bool Octree::addDynamicCollider(Collider * coll)
{
  if (!coll->intersectB(&space)) return false;
  Bucket * b = getLowestBucket(coll);
  if (b != 0) b->addDynamicNode(coll);
  else return false;
  return true;
}

std::vector<Collision> & Octree::getCollisions()
{
  if (collisions.size() != 0)
    collisions.clear();
  for (unsigned int i = 0; i < allBuckets.size(); i++)
    checkBucketCollision(allBuckets[i], collisions);

  return collisions;
}

void Octree::cleanDynamic()
{
  for (unsigned int i = 0; i < allBuckets.size(); i++)
  {
    allBuckets[i]->cleanDynamic();
  }
}
