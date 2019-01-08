#include "Game/Object/coinOnCollision.h"

CoinOnCollision::CoinOnCollision(double & deltaTime, Object * object) : Component(object), dt(deltaTime)
{
  object->subscribe("Respawn", this);
  object->subscribe("collision", this);
  transform = object->getComponent<Transform>();
}

CoinOnCollision::~CoinOnCollision()
{

}

void CoinOnCollision::receiveMessage(const std::string & message, void * data) 
{
  if (message == "collision") {
	if (!hit) {
	  object->sendMessage("explosion", &transform->getPos());
	  object->sendMessage("addScore", &toAddScore);
	}
    transform->getScale() = Vec3<float>(0, 0, 0);
    hit = true;
  } else if (message == "Respawn") {
    transform->getScale() = Vec3<float>(1, 1, 1);
    hit = false;
  }
}