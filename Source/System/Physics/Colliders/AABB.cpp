#include "System/Physics/Colliders/AABB.h"

AABB::AABB(Vec3<float> pos, Vec3<float> radius) : Collider()
{
  setPos(pos);
  scale = radius;
}

AABB::AABB()
{

}

Vec3<float> AABB::intersectA(Collider * other)
{
  AABB * aabb = dynamic_cast<AABB*>(other);
  if (aabb)
  {
    Vec3<float> p = getPos();
    Vec3<float> otherPos = aabb->getPos();
    Vec3<float> otherRadius = aabb->getRadius();
    Vec3<float> resolution = (p-otherPos) / (scale + otherRadius);
  
    resolution[0] = (std::fabs(resolution[0]) > std::fabs(resolution[1])) ? (std::fabs(resolution[0]) > std::fabs(resolution[2])) ? resolution[0] : 0 : 0;
    resolution[1] = (std::fabs(resolution[1]) > std::fabs(resolution[0])) ? (std::fabs(resolution[1]) > std::fabs(resolution[2])) ? resolution[1] : 0 : 0;
    resolution[2] = (std::fabs(resolution[2]) > std::fabs(resolution[0])) ? (std::fabs(resolution[2]) > std::fabs(resolution[1])) ? resolution[2] : 0 : 0;
    resolution = resolution.normalize();
    resolution[0] = (resolution[0]) * 0.002;
    resolution[1] = (resolution[1]) * 0.002;
    resolution[2] = (resolution[2]) * 0.002;

    return resolution;
  }
  return Vec3<float>();
}

bool AABB::intersectB(Collider * other)
{
  AABB * aabb = dynamic_cast<AABB*>(other);
  if (aabb)
  {
    Vec3<float> p = getPos();
    
    Vec3<float> otherPos = aabb->getPos();
    Vec3<float> otherRadius = aabb->getRadius();

    if (std::abs(otherPos[0] - p[0]) > otherRadius[0] + scale[0]) return false;
    if (std::abs(otherPos[1] - p[1]) > otherRadius[1] + scale[1]) return false;
    if (std::abs(otherPos[2] - p[2]) > otherRadius[2] + scale[2]) return false;

    return true;
  }

  return false;
}

Vec3<float> AABB::getRadius()
{
  return scale;
}

void AABB::setRadius(Vec3<float> rad)
{
  scale = rad;
}

AABB::~AABB()
{

}
