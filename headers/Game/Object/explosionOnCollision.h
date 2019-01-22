#ifndef EXPLOSIONONCOLLISION__
#define EXPLOSIONONCOLLISION__

#include "System/Engine/EngineObjects/object.h"
#include "System/Physics/collisionModule.h"
#include "System/Engine/EngineObjects/transform.h"


class ExplosionOnCollision : public Component
{
private:
  Transform * transform;
  std::string tag;
public:
  ExplosionOnCollision(std::string collisionTag, Object * object);
  virtual ~ExplosionOnCollision();
  void receiveMessage(const std::string & message, void* data);
};

#endif