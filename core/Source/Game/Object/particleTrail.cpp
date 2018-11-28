#include "Game/Object/particleTrail.h"

ParticleTrail::ParticleTrail(Vec3<float> * rotation, Vec3<float> * pos, Object * object, Vec3<float> offset) : ParticleSystem(object) 
{
  rot = rotation;
  position = pos;
  this->offset = offset;
}

ParticleTrail::~ParticleTrail()
{

}

void ParticleTrail::update()
{
  Matrix<float> rotation;
  rotation = rotation.rotation(*rot);


  bool moved = false;
  float distance = 0;
  float decreaseTime = 1 / 120.0f;
  Vec3<float> distanceMoved = (*position - lastPosition);
  Vec3<float> spawnPosition = ((position) ? *position + rotation.multiplyByVector(offset) : Vec3<float>());

  for (int i = 0; i < 3; i++) {
    distance += (*position)[i] - lastPosition[i];
  }
  if (std::abs(distance) > 0.005) moved = true;

  while (particleInformation.size() < instances.size()) particleInformation.push_back(ParticleInfo());
  for (unsigned int i = 0; i < instances.size(); i++) {
    instances[i]->getPos() += particleInformation[i].force;
    instances[i]->getScale() = Vec3<float>(0.15, 0.15, 0.15) * ((0 < particleInformation[i].lifeTime) ? particleInformation[i].lifeTime : 0);

    instances[i]->getRot() += particleInformation[i].force * 25;

    particleInformation[i].force *= 0.99999f;
    particleInformation[i].lifeTime -= decreaseTime;
    if (moved && particleInformation[i].lifeTime < 0) {
      instances[i]->getPos() = spawnPosition;
      particleInformation[i].lifeTime = (float)rand() / RAND_MAX;
      particleInformation[i].force = Vec3<float>(((float)rand() / RAND_MAX * 2 - 1) * 1.2, (float)rand() / RAND_MAX * 0.8, ((float)rand() / RAND_MAX)) + distanceMoved; 
      particleInformation[i].force = rotation.multiplyByVector(particleInformation[i].force);
      particleInformation[i].force.normalize();

      particleInformation[i].force *= std::abs(distance) * 0.15;
  }
  lastPosition = *position;
}

}