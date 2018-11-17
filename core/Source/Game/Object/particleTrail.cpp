#include "Game/Object/particleTrail.h"

ParticleTrail::ParticleTrail(Vec3<float> * rotation, Vec3<float> * pos, Object * object) : ParticleSystem(object) 
{
  rot = rotation;
  position = pos;
}

ParticleTrail::~ParticleTrail()
{

}

void ParticleTrail::update()
{
  Matrix<float> rotation;
  bool moved = false;
  float distance = 0;
  for (int i = 0; i < 3; i++) {
    distance += (*position)[i] - lastPosition[i];
  }
  if (std::abs(distance) > 0.005) moved = true;
  rotation = rotation.rotation(*rot);
  while (particleInformation.size() < instances.size()) particleInformation.push_back(ParticleInfo());
  for (unsigned int i = 0; i < instances.size(); i++) {
    instances[i]->getPos() += particleInformation[i].force;
    instances[i]->getScale() = Vec3<float>(0.2, 0.2, 0.2) * ((0 < particleInformation[i].lifeTime) ? particleInformation[i].lifeTime : 0);

    instances[i]->getRot() += particleInformation[i].force * 50;

    particleInformation[i].force *= 0.99999f;
    particleInformation[i].lifeTime -= 1 / 45.0f;
    if (particleInformation[i].lifeTime < 0 && moved) {
      instances[i]->getPos() = ((position) ? *position : Vec3<float>());
      particleInformation[i].lifeTime = (float)rand() / RAND_MAX;
      particleInformation[i].force = Vec3<float>(((float)rand() / RAND_MAX * 2 - 1) * 1.2, (float)rand() / RAND_MAX * 0.8, ((float)rand() / RAND_MAX)) + (*position - lastPosition);
      particleInformation[i].force = rotation.multiplyByVector(particleInformation[i].force);
      particleInformation[i].force.normalize();

      particleInformation[i].force *= std::abs(distance) * 0.2;
  }
  lastPosition = *position;
}

}