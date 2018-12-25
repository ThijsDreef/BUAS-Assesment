#ifndef ABSTRACTSCENEFACTORY__
#define ABSTRACTSCENEFACTORY__
#include "System/Engine/engine.h"
#include "System/Engine/scene.h"

class AbstractSceneFactory 
{
public:
  AbstractSceneFactory();
  ~AbstractSceneFactory();
  virtual Scene * createScene(const std::string & sceneName, Engine & engine) = 0;
};

#endif