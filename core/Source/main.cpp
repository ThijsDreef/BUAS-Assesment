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
#include "Game/Object/playerMovement.h"
#include "Game/Object/followCamera.h"

#include <iostream>

int main(int argc, char const *argv[])
{
  Engine engine(1/60.0f, 1920, 1080);
  engine.getInput()->setMouseLock(true);
  std::vector<Object*> objects;

  Object * ice = new Object({});
  ice->addComponent(new Transform(Vec3<float>(0, 0, 0), Vec3<float>(15, 1, 15), Vec3<float>(0, 0, 0), "ice", {}, ice));

  Object * player = new Object({});
  player->addComponent(new Transform(Vec3<float>(0, 1, 0), Vec3<float>(1, 1, 1), Vec3<float>(), "icoSphere", {}, player));
  player->addComponent(new PlayerMovement(&player->getComponent<Transform>()->getPos(), engine.getInput(), player));

  Object * camera = new Object({});
  camera->addComponent(new TextDebug<unsigned int>("fps: ", Vec2<float>(-800, 500), &engine.frames, camera));
  camera->addComponent(new FollowCamera(&player->getComponent<Transform>()->getPos(), camera, Vec3<float>(0, 5, 15), Vec3<float>(35.264 * 1.5, 0, 0)));

  objects.push_back(ice);
  objects.push_back(camera);
  objects.push_back(player);

  DefferedRenderModule * renderModule = new DefferedRenderModule(engine.getGeoLib(), engine.getMatLib(), engine.getShaderManger(), engine.getWidth(), engine.getHeight());
  renderModule->updateOrthoGraphic(1920, 1080, 0.01, 100.0f);

  engine.start(new Scene
    (
      objects,
      {
        {
          new CollisionModule(50, 4)
        },
        {
          renderModule
        },
        {
          new UiRenderer("fonts/text", engine.getShaderManger(), 1920, 1080)
        }
      }
    ));
  return 0;
}
