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
#include "Game/Object/particleTrail.h"

#include "Game/Object/rotateToMouse.h"


#include <iostream>

int main(int argc, char const *argv[])
{
  Engine engine("pingu on a mission", 1920, 1080, 32, true, 1/60.0f);

  std::vector<Object*> objects;
  Texture * texture = new Texture("models/textures/iceTexture.png");
  engine.getMatLib()->addTexture("iceTexture", texture);
  Material mat;
  mat.texture = texture->getId();
  mat.color = Vec4<float>(0, 0, 1, 1);

  
  engine.getMatLib()->addMaterial("blue", Material(Vec4<float>(0, 0, 1, 1)));
  engine.getMatLib()->addMaterial("lightBlue", Material(Vec4<float>(0.37, 0.61, 1, 1)));
  engine.getMatLib()->addMaterial("red", mat);



  Object * cube = new Object({});
  cube->addComponent(new Transform(Vec3<float>(3, 3, 1), Vec3<float>(0.2, 0.2, 0.2), Vec3<float>(0, 90, 0), "snowman", {}, cube));
  cube->addComponent(new CollisionComponent(false, new AABB(Vec3<float>(0, 0, 0), Vec3<float>(1.5, 2.5, 1.5)), cube->getComponent<Transform>(), cube));

  for (int x = -3; x < 3; x++) {
    for (int z = -3; z < 3; z++) {
      Object * o = new Object({});
      o->addComponent(new Transform(Vec3<float>(x * 20, 0, z * 20), Vec3<float>(10, 1, 10), Vec3<float>(), "cube", {"red"}, o));
      o->addComponent(new CollisionComponent(true, new AABB(Vec3<float>(), Vec3<float>(10, 1, 10)), o->getComponent<Transform>(), o, "ground"));
      objects.push_back(o);
    }
  }

  for (int x = -10; x < 10; x ++) {
    Object * o = new Object({});
    o->addComponent(new Transform(Vec3<float>(19, 2, 1 + x * 2), Vec3<float>(1, 1, 1), Vec3<float>(), "railing", {}, o));
    o->addComponent(new CollisionComponent(true, new AABB(Vec3<float>(), Vec3<float>(1, 5, 1)), o->getComponent<Transform>(), o, "none"));


    Object * ot = new Object({});
    ot->addComponent(new Transform(Vec3<float>(-20, 2, 1 + x * 2), Vec3<float>(1, 1, 1), Vec3<float>(), "railing", {}, ot));
    ot->addComponent(new CollisionComponent(true, new AABB(Vec3<float>(), Vec3<float>(1, 5, 1)), ot->getComponent<Transform>(), ot, "none"));


    objects.push_back(o);
    objects.push_back(ot);
  }

  for (int z = -10; z < 10; z ++) {
    Object * o = new Object({});
    o->addComponent(new Transform(Vec3<float>(0.75 + z * 2, 2, 19.25), Vec3<float>(1, 1, 1), Vec3<float>(0, 90, 0), "railing", {}, o));
    o->addComponent(new CollisionComponent(true, new AABB(Vec3<float>(), Vec3<float>(1, 5, 1)), o->getComponent<Transform>(), o, "none"));


    Object * ot = new Object({});
    ot->addComponent(new Transform(Vec3<float>(0.75 + z * 2, 2, -19.75), Vec3<float>(1, 1, 1), Vec3<float>(0, 90, 0), "railing", {}, ot));
    ot->addComponent(new CollisionComponent(true, new AABB(Vec3<float>(), Vec3<float>(1, 5, 1)), ot->getComponent<Transform>(), ot, "none"));


    objects.push_back(o);
    objects.push_back(ot);
  }

  Object * player = new Object({});
  player->addComponent(new Transform(Vec3<float>(0, 5, 0), Vec3<float>(1, 1, 1), Vec3<float>(0, 0, 0), "pinguin", {}, player));
  player->addComponent(new PlayerMovement(&player->getComponent<Transform>()->getPos(), &player->getComponent<Transform>()->getRot(), engine.getInput(), player));
  player->addComponent(new RotateToMouse(&player->getComponent<Transform>()->getRot(), engine.getInput(), player));
  player->addComponent(new CollisionComponent(false, new AABB(Vec3<float>(0, 0, 0), Vec3<float>(1.5, 1.45, 1.5)), player->getComponent<Transform>(), player));


  Object * particles = new Object({});
  ParticleTrail * particleComponet = new ParticleTrail(&player->getComponent<Transform>()->getRot(), &player->getComponent<Transform>()->getPos(), particles, Vec3<float>(0, -0.9, 0.5));

  for (unsigned int i = 0; i < 500; i++) {
    Object * o = new Object({});
    o->addComponent(new Transform(Vec3<float>(0, 0, 0), Vec3<float>(0.05, 0.05, 0.05), Vec3<float>(), "cube", {"red"}, o));
    objects.push_back(o);
    particleComponet->addToInstance(o->getComponent<Transform>());
  }
  particles->addComponent(particleComponet);

  Object * camera = new Object({});
  camera->addComponent(new TextDebug<unsigned int>("fps: ", Vec2<float>(-1, 1), &engine.frames, camera));
  camera->addComponent(new FollowCamera(&player->getComponent<Transform>()->getPos(), camera, Vec3<float>(-50, 52, 50), Vec3<float>(35.2, 45, 0), Vec3<float>(1, 0, 1)));

  // objects.push_back(ice);
  objects.push_back(camera);
  objects.push_back(cube);


  objects.push_back(player);
  objects.push_back(particles);

  CollisionModule * collisionModule = new CollisionModule(200, 4);
  player->addComponent(new TextDebug<unsigned int>("collisionCount: ", Vec2<float>(-1, 0.8), &collisionModule->collisionCount, player));

  DefferedRenderModule * renderModule = new DefferedRenderModule(engine.getGeoLib(), engine.getMatLib(), engine.getShaderManger(), engine.getWidth(), engine.getHeight());
  renderModule->updateOrthoGraphic(2560, 1440, -1000.0f, 1000.0f);

  engine.start(new Scene
    (
      objects,
      {
        { 
          collisionModule
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
