#ifndef DEATHWALL__
#define DEATHWALL__

#include "System/Engine/EngineObjects/object.h"
#include "System/Engine/EngineObjects/transform.h"


class DeathWall : public Component
{
private:
  float yLimit;
  float * targetY;
public:
  void update();
  DeathWall(float yLimit, Object * object);
  virtual ~DeathWall();
};

#endif