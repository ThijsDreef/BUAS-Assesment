#include "System/Engine/EngineObjects/particleSystem.h"

ParticleSystem::ParticleSystem(Object * object) : InstancedTransform(object)
{
  srand(29313);
}

void ParticleSystem::update()
{
  while (particleInformation.size() < instances.size()) particleInformation.push_back(ParticleInfo());
  for (unsigned int i = 0; i < instances.size(); i++) {
    instances[i]->getPos() += particleInformation[i].force;
    instances[i]->getScale() = Vec3<float>(particleInformation[i].lifeTime * 0.5, particleInformation[i].lifeTime * 0.5, particleInformation[i].lifeTime * 0.5);

    instances[i]->getRot() += particleInformation[i].force * 50;

    particleInformation[i].force *= 0.99999f;
    particleInformation[i].lifeTime -= 1 / 300.0f;
    if (particleInformation[i].lifeTime < 0) {
      instances[i]->getPos() = ((position) ? Vec3<float>() : *position) + Vec3<float>(0, 5, 0);
      particleInformation[i].lifeTime = 1.0;
      particleInformation[i].force = Vec3<float>(((float)rand() / RAND_MAX) * 2 - 1.0f, ((float)rand() / RAND_MAX) * 2 - 1.0f, ((float)rand() / RAND_MAX) * 2 - 1.0f);
      particleInformation[i].force.normalize();
      particleInformation[i].force *= 0.05;
    }
  }
}

ParticleSystem::~ParticleSystem()
{

}