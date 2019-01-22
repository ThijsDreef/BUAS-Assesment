#include "Game/Object/explosionOnCollision.h"

ExplosionOnCollision::ExplosionOnCollision(std::string collisionTag, Object * object) : Component(object)
{
  tag = collisionTag;
  transform = object->getComponent<Transform>();
  object->subscribe("collision", this);
}

ExplosionOnCollision::~ExplosionOnCollision()
{

}

void ExplosionOnCollision::receiveMessage(const std::string & message, void* data)
{
  if (message == "collision")
  {
    CollisionData * collisionData = static_cast<CollisionData*>(data);
		if (collisionData->other->tag == tag) {
      object->sendMessage("explosion", &transform->getPos());
    }
  }
}