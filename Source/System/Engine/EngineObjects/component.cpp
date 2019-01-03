#include "System/Engine/EngineObjects/component.h"
#include <iostream>

Component::Component(Object * object)
{
  this->object = object;
}

Component::~Component()
{

}

void Component::start()
{

}
bool Component::isDead()
{
  return dead;
}

void Component::receiveMessage(const std::string & message, void* data)
{

}

bool Component::isRemoved()
{
  return refCounter < 0;
}

void Component::setDead()
{
  dead = true;
}

void Component::setRemoved()
{
  refCounter--;
}

void Component::added()
{
  refCounter++;
}

void Component::update()
{

}

Object* Component::getObject()
{
  return object;
}
