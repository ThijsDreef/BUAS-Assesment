#ifndef ParticleTrail__
#define ParticleTrail__

#include "System/Engine/EngineObjects/particleSystem.h"

class ParticleTrail : public ParticleSystem 
{
private:
  int spawnCount = 10;
  Vec3<float> * rot;
  Vec3<float> lastPosition;
  Vec3<float> offset;
  double & dt;
public:
    ParticleTrail(Vec3<float> * rotation, Vec3<float> * position, double & deltaTime, Object * object, Vec3<float> offset = Vec3<float>());
    ~ParticleTrail();
    void update();
};


#endif