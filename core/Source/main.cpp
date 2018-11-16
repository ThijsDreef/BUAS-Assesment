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

#include "Game/Object/playerMovement.h"
#include "Game/Object/followCamera.h"
#include "Game/Object/particleGun.h"

#include "Game/Object/rotateToMouse.h"


#include <iostream>

int main(int argc, char const *argv[])
{
  Engine engine("pingu on a mission", 2560, 1440, 32, true, 1/60.0f);

  std::vector<Object*> objects;

  Material blue = Material(Vec4<float>(0, 0, 1, 1));
  engine.getMatLib()->addMaterial("blue", blue);

  Object * cube = new Object({});
  cube->addComponent(new Transform(Vec3<float>(1, 1, 1), Vec3<float>(0.2, 0.2, 0.2), Vec3<float>(0, 90, 0), "snowman", {}, cube));

  Object * ice = new Object({});
  InstancedTransform * instancedTransform = new InstancedTransform(ice);
  for (int x = -10; x < 10; x++) {
    for (int y = -0; y < 1; y++)  {
      for (int z = -10; z < 10; z++) {
        Object * o = new Object({});
        o->addComponent(new Transform(Vec3<float>(x * 2.2, y * 2.2, z * 2.2), Vec3<float>(1, 1, 1), Vec3<float>(), "cube", {"blue"}, o));
        instancedTransform->addToInstance(o->getComponent<Transform>()); 
        objects.push_back(o);
      }
    }
  }
  ice->addComponent(instancedTransform);


  Object * player = new Object({});
  player->addComponent(new Transform(Vec3<float>(0, 1, 0), Vec3<float>(1, 1, 1), Vec3<float>(0, 180, 0), "pinguin", {}, player));
  player->addComponent(new PlayerMovement(&player->getComponent<Transform>()->getPos(), &player->getComponent<Transform>()->getRot(), engine.getInput(), player));
  player->addComponent(new RotateToMouse(&player->getComponent<Transform>()->getRot(), engine.getInput(), player));

  Object * particles = new Object({});
  ParticleGun * particleComponet = new ParticleGun(&player->getComponent<Transform>()->getRot(), &player->getComponent<Transform>()->getPos(), particles);

  for (unsigned int i = 0; i < 1000; i++) {
    Object * o = new Object({});
    o->addComponent(new Transform(Vec3<float>(0, 0, 0), Vec3<float>(0.05, 0.05, 0.05), Vec3<float>(), "icoSphere", {"blue"}, o));
    objects.push_back(o);
    particleComponet->addToInstance(o->getComponent<Transform>());
  }
  particles->addComponent(particleComponet);

  Object * camera = new Object({});
  camera->addComponent(new TextDebug<unsigned int>("fps: ", Vec2<float>(-1, 1), &engine.frames, camera));
  camera->addComponent(new FollowCamera(&player->getComponent<Transform>()->getPos(), camera, Vec3<float>(-50, 50, 50), Vec3<float>(35.2, 45, 0)));

  objects.push_back(ice);
  objects.push_back(camera);
  objects.push_back(cube);
  objects.push_back(particles);


  objects.push_back(player);

  DefferedRenderModule * renderModule = new DefferedRenderModule(engine.getGeoLib(), engine.getMatLib(), engine.getShaderManger(), engine.getWidth(), engine.getHeight());
  renderModule->updateOrthoGraphic(1920, 1080, -1000.0f, 1000.0f);

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
          new UiRenderer("fonts/text", engine.getShaderManger(), engine.getHeight(), engine.getWidth())
        }
      }
    ));
  return 0;
}
