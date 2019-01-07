#ifndef SCALEONRESPAWN__
#define SCALEONRESPAWN__

#include "System/Engine/EngineObjects/object.h"
#include "System/Engine/EngineObjects/transform.h"
#include "System/Physics/collisionComponent.h"
#include "Math/vec3.h"

class ScaleOnRespawn : public Component
{
private:
  Vec3<float> min;
  Vec3<float> max;
  Transform * transform;
public:
  ScaleOnRespawn(Vec3<float> minScale, Vec3<float> maxScale, Object * subscribeObject, Object * object);
  virtual ~ScaleOnRespawn();
  void receiveMessage(const std::string & message, void * data);
};

#endif