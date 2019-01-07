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
  bool paused;
  double lastTimeScale = 0;
public:
  PauseEvent(Object * subscribeObject, Engine & engine, Object * object);
  virtual ~PauseEvent();
  void receiveMessage(const std::string & message, void * data);
};


#endif