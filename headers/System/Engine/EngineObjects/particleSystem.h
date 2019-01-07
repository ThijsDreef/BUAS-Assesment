#ifndef PARTICLESYSTEM__
#define PARTICLESYSTEM__

#include "System/Engine/EngineObjects/InstancedTransform.h"

struct ParticleInfo {
  Vec3<float> force;
  float lifeTime = 0;
};

class ParticleSystem : public InstancedTransform 
{
protected:
  std::vector<ParticleInfo> particleInformation;
  Vec3<float> * position;
public: 
  ParticleSystem(Object * object);
  virtual ~ParticleSystem();
  virtual void update();
};
#endif