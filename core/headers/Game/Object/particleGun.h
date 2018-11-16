#ifndef PARTICLEGUN__
#define PARTICLEGUN__

#include "System/Engine/EngineObjects/particleSystem.h"

class ParticleGun : public ParticleSystem 
{
private:
  int spawnCount = 10;
  Vec3<float> * rot;
public:
    ParticleGun(Vec3<float> * rotation, Vec3<float> * position, Object * object);
    ~ParticleGun();
    void update();
};


#endif