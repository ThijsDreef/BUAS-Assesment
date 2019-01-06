#include "Game/Object/scaleOnRespawn.h"

ScaleOnRespawn::ScaleOnRespawn(Vec3<float> minScale, Vec3<float> maxScale, Object * subscribeObject, Object * object) : Component(object)
{
  max = maxScale;
  min = minScale;
  subscribeObject->subscribe("Respawn", this);
  transform = object->getComponent<Transform>();
}

ScaleOnRespawn::~ScaleOnRespawn()
{

}

void ScaleOnRespawn::receiveMessage(const std::string & message, void * data)
{
  if (message == "Respawn")
  {
    Vec3<float> random = Vec3<float>((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
    Vec3<float> newScale = min + (max - min) * random;
    transform->getScale() = newScale;
    CollisionComponent * coll = transform->getObject()->getComponent<CollisionComponent>();
    if (coll) coll->getCollider()->setScale(transform->getScale());
  }
}