#ifndef PARTICLEGUN__
#define PARTICLEGUN__

#include "System/Input/input.h"
#include "System/Engine/EngineObjects/particleSystem.h"

class ParticleGun : public ParticleSystem
{
private:
  Vec3<float> * spawnPosition;
  Vec3<float> * rotation;
  Input * input;
public:
  ParticleGun(Vec3<float> * spawnPos, Vec3<float> * rot, Input * input, Object * object);
  ~ParticleGun();
  void update();
};

#endif