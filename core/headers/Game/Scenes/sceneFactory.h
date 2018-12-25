#ifndef SCENEFACTORY__
#define SCENEFACTORY__

#include "System/Engine/scene.h"
#include "System/Engine/engine.h"
#include "System/Engine/EngineObjects/orbitalCamera.h"
#include "System/Graphics/defferedRenderModule.h"
#include "System/Graphics/renderModule.h"
#include "System/Physics/collisionModule.h"
#include "System/Physics/octree.h"
#include "System/Engine/EngineObjects/fpsCamera.h"
#include "System/Graphics/Ui/font.h"
#include "System/Graphics/Ui/uiRenderer.h"
#include "System/Graphics/Ui/uiText.h"
#include "System/Engine/EngineObjects/textDebug.h"
#include "System/Engine/EngineObjects/particleSystem.h"
#include "Game/Scenes/abstractSceneFactory.h"
#include "Game/Object/playerMovementStateMachine.h"
#include "Game/Object/playerMovement.h"
#include "Game/Object/followCamera.h"
#include "Game/Object/particleTrail.h"
#include "Game/Object/rotateTransform.h"
#include "Game/Object/trick.h"
#include "Game/Object/score.h"
#include "Game/Object/waveCustomTransform.h"
#include "Game/Object/rotateToMouse.h"
#include "Game/Object/deathWall.h"
#include "Game/Object/sinkAble.h"
#include "Game/Object/chunkSpawner.h"
#include "Game/Object/autoScroller.h"
#include "Game/Object/loadSceneEvent.h"


//WARNING ALL SCENES USED NEED TO BE DELETED BY USER
//
//UNLESS USED BY ENGINE

class SceneFactory : public AbstractSceneFactory {
public:
  SceneFactory();
  Scene * createScene(const std::string & sceneName, Engine & engine);
  Scene * createEndlessRunnerScene(Engine & engine);
  Scene * createMainScene(Engine & engine);
  virtual ~SceneFactory();
};

#endif