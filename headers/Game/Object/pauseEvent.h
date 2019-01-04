#ifndef PAUSEEVENT__
#define PAUSEEVENT__

#include "System/Engine/EngineObjects/object.h"
#include "System/Graphics/Ui/uiText.h"

#include "Game/Scenes/abstractSceneFactory.h"
#include "System/Engine/engine.h"

class PauseEvent : public UIText
{
private:
  Engine & engineObject;
public:
  PauseEvent(Object * subscribeObject, Engine & engine, Object * object);
  ~PauseEvent();
  void receiveMessage(const std::string & message, void * data);
};


#endif