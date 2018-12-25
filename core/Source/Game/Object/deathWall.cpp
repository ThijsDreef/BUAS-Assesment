#include "Game/Object/deathWall.h"

DeathWall::DeathWall(float yLimit, Object * object) : Component(object)
{
  this->yLimit = yLimit;
  targetY = &object->getComponent<Transform>()->getPos()[1];
}

DeathWall::~DeathWall()
{

}

void DeathWall::update()
{
  if (yLimit > *targetY) object->sendMessage("dead", 0);
}
