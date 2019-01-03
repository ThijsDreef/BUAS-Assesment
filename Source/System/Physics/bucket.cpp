#include "System/Physics/bucket.h"

Bucket::Bucket(AABB aabb, Bucket * top, int recursiveCount)
{
  recursiveCount--;
  parent = top;
  bb = aabb;
  Vec3<float> pos = bb.getPos();
  Vec3<float> rad = bb.getRadius() * 0.5;
  if (recursiveCount <= 0) return;
  //make this a for loop you dummy
  children.push_back(new Bucket(AABB(Vec3<float>(pos[0] - rad[0], pos[1] - rad[1], pos[2] - rad[2]), rad * 0.5), this, recursiveCount));
  children.push_back(new Bucket(AABB(Vec3<float>(pos[0] - rad[0], pos[1] + rad[1], pos[2] - rad[2]), rad * 0.5), this, recursiveCount));
  children.push_back(new Bucket(AABB(Vec3<float>(pos[0] - rad[0], pos[1] - rad[1], pos[2] + rad[2]), rad * 0.5), this, recursiveCount));
  children.push_back(new Bucket(AABB(Vec3<float>(pos[0] - rad[0], pos[1] + rad[1], pos[2] + rad[2]), rad * 0.5), this, recursiveCount));
  children.push_back(new Bucket(AABB(Vec3<float>(pos[0] + rad[0], pos[1] - rad[1], pos[2] - rad[2]), rad * 0.5), this, recursiveCount));
  children.push_back(new Bucket(AABB(Vec3<float>(pos[0] + rad[0], pos[1] + rad[1], pos[2] - rad[2]), rad * 0.5), this, recursiveCount));
  children.push_back(new Bucket(AABB(Vec3<float>(pos[0] + rad[0], pos[1] - rad[1], pos[2] + rad[2]), rad * 0.5), this, recursiveCount));
  children.push_back(new Bucket(AABB(Vec3<float>(pos[0] + rad[0], pos[1] + rad[1], pos[2] + rad[2]), rad * 0.5), this, recursiveCount));
}

Bucket::~Bucket()
{
  for (unsigned int i = 0; i < children.size(); i++)
    delete children[i];
}

void Bucket::Bucket::addStaticNode(Collider * coll)
{
  staticNodes.push_back(coll);
}

void Bucket::Bucket::addDynamicNode(Collider * coll)
{
  dynamicNodes.push_back(coll);
}

bool Bucket::removeStaticNode(Collider * coll)
{
  for (unsigned int i = 0; i < staticNodes.size(); i++)
  {
    if (staticNodes[i] == coll)
    {
      staticNodes.erase(staticNodes.begin() + i);
      return true;
    }
  }

  for (unsigned int i = 0; i < children.size(); i++)
  {
    if (children[i]->removeStaticNode(coll))
      return true;
  }
  return false;
}

bool Bucket::removeDynamicNode(Collider * coll)
{
  for (unsigned int i = 0; i < dynamicNodes.size(); i++)
  {
    if (dynamicNodes[i] == coll)
    {
      dynamicNodes.erase(dynamicNodes.begin() + i);
      return true;
    }
  }

  for (unsigned int i = 0; i < children.size(); i++)
  {
    if (children[i]->removeDynamicNode(coll))
      return true;
  }
  return false;
}

bool Bucket::queryInside(Collider * coll)
{
    return bb.intersectB(coll);
}

std::vector<Bucket*> Bucket::queryLowestBucket(Collider * coll)
{
  std::vector<Bucket*> found;
  for (unsigned int i = 0; i < children.size(); i++)
  {
    if (children[i]->queryInside(coll))
      found.push_back(children[i]);
  }
  return found;
}

std::vector<Bucket*> & Bucket::getChildren()
{
  return children;
}

std::vector<Collider*> & Bucket::getStatic()
{
  return staticNodes;
}

std::vector<Collider*> & Bucket::getDynamic()
{
  return dynamicNodes;
}

void Bucket::cleanDynamic()
{
  dynamicNodes.clear();
}
