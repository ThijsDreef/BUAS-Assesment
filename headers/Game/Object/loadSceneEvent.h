#ifndef LOADSCENEEVENT__
#define LOADSCENEEVENT__

#include "System/Engine/EngineObjects/object.h"
#include "Game/Scenes/abstractSceneFactory.h"
#include "System/Engine/engine.h"

class LoadSceneEvent : public Component
{
private:
  std::string scene;
  std::string event;
  Engine & engineObject;
  AbstractSceneFactory * sceneFactory;
public:
  LoadSceneEvent(const std::string event, const std::string scene, Object * subcribeObject, AbstractSceneFactory * sceneFactory, Engine & engine, Object * object);
  virtual ~LoadSceneEvent();
  void receiveMessage(const std::string & message, void * data);
};


#endif