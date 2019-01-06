#include "Game/Object/explosionEvent.h"

ExplosionEvent::ExplosionEvent(Object * subscribeObject, double & deltaTime, Object * object) : ParticleSystem(object), dt(deltaTime)
{
  subscribeObject->subscribe("explosion", this);
}

ExplosionEvent::~ExplosionEvent()
{

}

void ExplosionEvent::update()
{
  while (particleInformation.size() < instances.size()) particleInformation.push_back(ParticleInfo());
  for (unsigned int i = 0; i < instances.size(); i++) {
    instances[i]->getPos() += particleInformation[i].force * dt;
    instances[i]->getScale() = (particleInformation[i].lifeTime < 0) ? Vec3<float>(0, 0, 0) : Vec3<float>(particleInformation[i].lifeTime, particleInformation[i].lifeTime, particleInformation[i].lifeTime);

    instances[i]->getRot() += particleInformation[i].force * 2 * dt;

    particleInformation[i].force.lerp(Vec3<float>(0, 0, 0), 1.0f - powf(0.99, dt));
    particleInformation[i].lifeTime -= dt;
  }
}

void ExplosionEvent::receiveMessage(const std::string & message, void* data)
{
  if (message == "explosion") {
    Vec3<float> spawnLocation = *static_cast<Vec3<float>*>(data);
    for (unsigned int i = 0; i < particleInformation.size(); i++) 
    {
      if (particleInformation[i].lifeTime < 0) 
      {
        instances[i]->getPos() = spawnLocation;
        particleInformation[i].lifeTime = 0.5;
        particleInformation[i].force = Vec3<float>(((float)rand() / RAND_MAX) * 2 - 1.0f, ((float)rand() / RAND_MAX) * 2 - 1.0f, ((float)rand() / RAND_MAX) * 2 - 1.0f);
        particleInformation[i].force = particleInformation[i].force.normalize() * 10;

      }
    }
  }
}