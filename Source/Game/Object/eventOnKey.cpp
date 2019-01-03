#include "Game/Object/eventOnKey.h"

EventOnKey::EventOnKey(std::vector<KeyEvent> events, Input * input, Object * object) : Component(object)
{
  keyEvents = events;
  this->input = input;
}

EventOnKey::~EventOnKey()
{

}

void EventOnKey::update()
{
  for (unsigned int i = 0; i < keyEvents.size(); i++)
  {
    if (input->getKeyDown(keyEvents[i].first)) object->sendMessage(keyEvents[i].second, 0);
  }
}