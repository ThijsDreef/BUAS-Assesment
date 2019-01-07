#include "Game/Object/pauseEvent.h"

PauseEvent::PauseEvent(Object * subscribeObject, Engine & engine, Object * object) : UIText("", Vec2<float>(0, 0.2),object), engineObject(engine)
{
  subscribeObject->subscribe("pause", this);
  subscribeObject->subscribe("unPause", this);
  scale = 2;
  shouldCenter = true;
  alpha = 0.6;
}

PauseEvent::~PauseEvent()
{

}

void PauseEvent::receiveMessage(const std::string & message, void * data)
{
  if (message == "pause") {
    setText("Paused");
    engineObject.timeScale = 0;
  } else if (message == "unPause") {
    if (!paused) return;
    setText("");
    engineObject.timeScale = 1;
  }
}