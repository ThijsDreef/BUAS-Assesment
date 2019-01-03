#include "Game/Object/loadSceneEvent.h"

LoadSceneEvent::LoadSceneEvent(const std::string event, const std::string scene, Object * subscribeObject, AbstractSceneFactory * sceneFactory, Engine & engine, Object * object) : Component(object), engineObject(engine)
{
  this->event = event;
  this->scene = scene;
  this->sceneFactory = sceneFactory;
  subscribeObject->subscribe(event, this);
}

LoadSceneEvent::~LoadSceneEvent()
{

}

void LoadSceneEvent::receiveMessage(const std::string & message, void * data)
{
  engineObject.popScene(true);
  engineObject.pushScene(sceneFactory->createScene(scene, engineObject));
}