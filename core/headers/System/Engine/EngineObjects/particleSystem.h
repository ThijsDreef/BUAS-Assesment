#ifndef PARTICLESYSTEM__
#define PARTICLESYSTEM__

#include "System/Engine/EngineObjects/InstancedTransform.h"

struct ParticleInfo {
  Vec3<float> force;
  float lifeTime = -1;
};

class ParticleSystem : public InstancedTransform 
{
protected:
  std::vector<ParticleInfo> particleInformation;
  Vec3<float> position;
public: 
  ParticleSystem(Object * object);
  ~ParticleSystem();
  void update();
};
#endif