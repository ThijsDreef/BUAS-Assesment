#ifndef SCENEFACTORY__
#define SCENEFACTORY__

#include "Game/Object/rotateTransform.h"
#include "System/Engine/scene.h"
#include "System/Engine/engine.h"
#include "System/Engine/EngineObjects/orbitalCamera.h"
#include "System/Graphics/defferedRenderModule.h"
#include "System/Physics/collisionModule.h"
#include "System/Physics/octree.h"
#include "System/Engine/EngineObjects/fpsCamera.h"
#include "System/Graphics/Ui/font.h"
#include "System/Graphics/Ui/uiRenderer.h"
#include "System/Graphics/Ui/uiText.h"
#include "System/Engine/EngineObjects/textDebug.h"
#include "System/Engine/EngineObjects/particleSystem.h"
#include "Game/Object/playerMovementStateMachine.h"
#include "Game/Object/playerMovement.h"
#include "Game/Object/followCamera.h"
#include "Game/Object/particleTrail.h"

#include "Game/Object/rotateToMouse.h"

#include "System/Engine/scene.h"

//WARNING ALL SCENES USED NEED TO BE DELETED BY USER
//
//UNLESS USED BY ENGINE

class SceneFactory {
public:
  SceneFactory();
  Scene * createMainScene(Engine & engine);
  virtual ~SceneFactory();
};

#endif