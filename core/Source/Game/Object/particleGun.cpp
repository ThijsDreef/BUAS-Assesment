#include "Game/Object/particleGun.h"

ParticleGun::ParticleGun(Vec3<float> * rotation, Vec3<float> * pos, Object * object) : ParticleSystem(object) 
{
  rot = rotation;
  position = pos;
}

ParticleGun::~ParticleGun()
{

}

void ParticleGun::update()
{
  Matrix<float> rotation;
  rotation = rotation.rotation(*rot);
  while (particleInformation.size() < instances.size()) particleInformation.push_back(ParticleInfo());
  for (unsigned int i = 0; i < instances.size(); i++) {
    instances[i]->getPos() += particleInformation[i].force;
    instances[i]->getScale() = Vec3<float>(particleInformation[i].lifeTime * 0.2, particleInformation[i].lifeTime * 0.2, particleInformation[i].lifeTime * 0.2);

    instances[i]->getRot() += particleInformation[i].force * 50;

    particleInformation[i].force *= 0.99999f;
    particleInformation[i].lifeTime -= 1 / 60.0f;
    if (particleInformation[i].lifeTime < 0) {
      instances[i]->getPos() = ((position) ? *position : Vec3<float>());
      particleInformation[i].lifeTime = (float)rand() / RAND_MAX;
      particleInformation[i].force = Vec3<float>(((float)rand() / RAND_MAX * 2 - 1) * 0.8, (float)rand() / RAND_MAX * 0.4, ((float)rand() / RAND_MAX) * 1.4);
      particleInformation[i].force = rotation.multiplyByVector(particleInformation[i].force);
      particleInformation[i].force.normalize();

      particleInformation[i].force *= 0.05;
  }
}

}