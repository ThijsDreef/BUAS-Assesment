#ifndef ParticleTrail__
#define ParticleTrail__

#include "System/Engine/EngineObjects/particleSystem.h"

class ParticleTrail : public ParticleSystem 
{
private:
  int spawnCount = 10;
  Vec3<float> * rot;
  Vec3<float> lastPosition;
public:
    ParticleTrail(Vec3<float> * rotation, Vec3<float> * position, Object * object);
    ~ParticleTrail();
    void update();
};


#endif