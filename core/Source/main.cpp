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
#include <iostream>

int main(int argc, char const *argv[])
{
  Engine engine(1/60.0f, 1920, 1080);
  engine.getInput()->setMouseLock(true);
  std::vector<Object*> objects;

  Object * camera = new Object({});
  camera->addComponent(new FpsCamera(engine.getInput(), camera));
  camera->addComponent(new TextDebug<unsigned int>("fps: ", Vec2<float>(-800, 500), &engine.frames, camera));
  AABB * coll = new AABB();
  coll->setRadius(Vec3<float>(1, 1, 1));
  coll->syncPos(&camera->getComponent<FpsCamera>()->getPos());
  camera->addComponent(new CollisionComponent(false, coll, 0, camera));


  Object * object = new Object({});
  object->addComponent(new Transform(Vec3<float>(0, -1, 0), Vec3<float>(1, 1, 1), Vec3<float>(0, 0, 0), "sponza", {"None"}, object));

  Object * bunny = new Object({});
  bunny->addComponent(new Transform(Vec3<float>(0, 1.8, 0), Vec3<float>(1, 1, 1), Vec3<float>(0, 0, 0), "bunny", {}, bunny));
  bunny->addComponent(new CollisionComponent(false, new AABB(Vec3<float>(0, 1.8, 0), Vec3<float>(0.5, 0.5, 0.5)), 0, bunny));
  bunny->getComponent<CollisionComponent>()->getCollider()->syncPos(&bunny->getComponent<Transform>()->getPos());

  // Object * instanced = new Object({});
  // InstancedTransform * it = new InstancedTransform(instanced);
  // for (int x = -10; x < 10; x++) {
  //   for (int y = 2; y < 10; y++) {
  //     for (int z = -10; z < 10; z++) {
  //       Object * o = new Object({});
  //       o->addComponent(new RotateTransform(Vec3<float>(x, 1.8 + y, z), Vec3<float>(0.2, 0.2, 0.2), Vec3<float>(0, 90, 0), "bunny", {"initialShadingGroup"}, engine.getInput(), o));
  //       objects.push_back(o);
  //       it->addToInstance(o->getComponent<Transform>());
  //     }
  //   }
  // }
  // instanced->addComponent(it);

  objects.push_back(bunny);
  objects.push_back(object);
  objects.push_back(camera);
  CollisionModule * module = new CollisionModule(50, 4);
  Object * collisionModuleDebug = new Object({});
  collisionModuleDebug->addComponent(new TextDebug<unsigned int>("collision count: ", Vec2<float>(-800, 400), &module->collisionCount, collisionModuleDebug));
  objects.push_back(collisionModuleDebug);


  engine.start(new Scene
    (
      objects,
      {
        {
          module,
        },
        {
          new DefferedRenderModule(engine.getGeoLib(), engine.getMatLib(), engine.getShaderManger(), engine.getWidth(), engine.getHeight()),
        },
        {
          new UiRenderer("fonts/text", engine.getShaderManger(), 1920, 1080)
        }
      }
    ));
  return 0;
}
