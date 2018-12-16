#include "Game/Scenes/sceneFactory.h"

SceneFactory::SceneFactory()
{

}

SceneFactory::~SceneFactory()
{

}

Scene * SceneFactory::createEndlessRunnerScene(Engine & engine)
{
  std::vector<Object*> objects;

  Object * autoScroller = new Object({});
  autoScroller->addComponent(new AutoScroller(Vec3<float>(60, 0, 0), Vec3<float>(-30 * 2, 0, 0), Vec3<float>(-7.5, 0, 0), engine.deltaTime, autoScroller));
  autoScroller->addComponent(new ChunkSpawner(autoScroller->getComponent<AutoScroller>(), autoScroller));
  objects.push_back(autoScroller);

  Object * player = new Object({});
  player->addComponent(new Transform(Vec3<float>(0, 3, 0), Vec3<float>(0.2, 0.2, 0.2), Vec3<float>(), "snowman", {}, player));
  player->addComponent(new PlayerMovement(&player->getComponent<Transform>()->getPos(), &player->getComponent<Transform>()->getRot(), engine.getInput(), engine.deltaTime, player));
  player->addComponent(new CollisionComponent(false, new AABB(Vec3<float>(0, 0, 0), Vec3<float>(2, 2, 2)), player->getComponent<Transform>(), player, "None"));
  player->addComponent(new TextDebug<float>("playerX: ", Vec2<float>(-1, 0.8), &player->getComponent<Transform>()->getPos()[0], player));
  autoScroller->getComponent<AutoScroller>()->addTransform(player->getComponent<Transform>());


  objects.push_back(player);

  Object * camera = new Object({});
  camera->addComponent(new FollowCamera(&player->getComponent<Transform>()->getRot(), camera, Vec3<float>(-50, 52, 50), Vec3<float>(35.2, 45, 0), Vec3<float>(1, 0, 1)));
  camera->addComponent(new TextDebug<unsigned int>("fps: ", Vec2<float>(-1, 1), &engine.frames, camera));
  objects.push_back(camera);

  for (int i = 0; i < 4; i++) {
    Object * platform = new Object({});
    platform->addComponent(new Transform(Vec3<float>(30 * i, 0, 0), Vec3<float>(10, 1, 10), Vec3<float>(), "cube", {}, platform));
    platform->addComponent(new CollisionComponent(true, new AABB(Vec3<float>(0, 0, 0), Vec3<float>(10, 1, 10)), platform->getComponent<Transform>(), platform, "ground"));
    autoScroller->getComponent<AutoScroller>()->addTransform(platform->getComponent<Transform>());
    objects.push_back(platform);
  }

  RenderModule * renderModule = new RenderModule(engine.getGeoLib(), engine.getMatLib(), engine.getShaderManger(), engine.getWidth(), engine.getHeight());
  renderModule->updateOrthoGraphic(2560, 1440, -1000.0f, 1000.0f);

  return new Scene(objects, {
    {new CollisionModule(200, 4)},
    {renderModule},
    {new UiRenderer("fonts/text", engine.getShaderManger(), engine.getHeight(), engine.getWidth())}
  });
}

Scene * SceneFactory::createMainScene(Engine & engine)
{
  std::vector<Object*> objects;

  //create snowman here
  Object * snowMan = new Object({});
  snowMan->addComponent(new Transform(Vec3<float>(3, 3, 1), Vec3<float>(0.2, 0.2, 0.2), Vec3<float>(0, 90, 0), "snowman", {}, snowMan));
  snowMan->addComponent(new CollisionComponent(false, new AABB(Vec3<float>(0, 0, 0), Vec3<float>(1.5, 2.5, 1.5)), snowMan->getComponent<Transform>(), snowMan));

  //for loop for INSERT AREA TARGET HERE
  for (int x = -3; x < 3; x++) {
    for (int z = -3; z < 3; z++) {
      Object * o = new Object({});
      o->addComponent(new Transform(Vec3<float>(x * 20, 0, z * 20), Vec3<float>(10, 1, 10), Vec3<float>(), "cube", {"red"}, o));
      o->addComponent(new CollisionComponent(true, new AABB(Vec3<float>(), Vec3<float>(10, 1, 10)), o->getComponent<Transform>(), o, "ground"));
      objects.push_back(o);
    }
  }
  Object * instancedFence = new Object({});
  InstancedTransform * it = new InstancedTransform(instancedFence);
  instancedFence->addComponent(it);
  //for loop for INSERT AREA TARGET HERE
  for (int x = -20; x < 20; x ++) {
    Object * o = new Object({});
    o->addComponent(new Transform(Vec3<float>(39, 2, 1 + x * 2), Vec3<float>(1, 1, 1), Vec3<float>(), "railing", {"None"}, o));
    o->addComponent(new CollisionComponent(true, new AABB(Vec3<float>(), Vec3<float>(1, 200, 1)), o->getComponent<Transform>(), o, "none"));


    Object * ot = new Object({});
    ot->addComponent(new Transform(Vec3<float>(-40, 2, 1 + x * 2), Vec3<float>(1, 1, 1), Vec3<float>(), "railing", {"None"}, ot));
    ot->addComponent(new CollisionComponent(true, new AABB(Vec3<float>(), Vec3<float>(1, 200, 1)), ot->getComponent<Transform>(), ot, "none"));

    it->addToInstance(o->getComponent<Transform>());
    it->addToInstance(ot->getComponent<Transform>());

    objects.push_back(o);
    objects.push_back(ot);
  }
  //for loop for INSERT AREA TARGET HERE
  for (int z = -20; z < 20; z ++) {
    Object * o = new Object({});
    o->addComponent(new Transform(Vec3<float>(0.75 + z * 2, 2, 39.25), Vec3<float>(1, 1, 1), Vec3<float>(0, 90, 0), "railing", {"None"}, o));
    o->addComponent(new CollisionComponent(true, new AABB(Vec3<float>(), Vec3<float>(1, 200, 1)), o->getComponent<Transform>(), o, "none"));


    Object * ot = new Object({});
    ot->addComponent(new Transform(Vec3<float>(0.75 + z * 2, 2, -39.75), Vec3<float>(1, 1, 1), Vec3<float>(0, 90, 0), "railing", {"None"}, ot));
    ot->addComponent(new CollisionComponent(true, new AABB(Vec3<float>(), Vec3<float>(1, 200, 1)), ot->getComponent<Transform>(), ot, "none"));

    it->addToInstance(o->getComponent<Transform>());
    it->addToInstance(ot->getComponent<Transform>());
    objects.push_back(o);
    objects.push_back(ot);
  }

  //create ScoreObject
  Object * scoreObject = new Object({});
  scoreObject->addComponent(new Score(Vec2<float>(-0.15, 1), scoreObject));
  //create TrickObject
  Object * trickObject = new Object({});
  trickObject->addComponent(new Trick(Vec2<float>(-0.2, 0.6), scoreObject->getComponent<Score>(), trickObject));

  //create Player
  Object * player = new Object({});
  player->addComponent(new Transform(Vec3<float>(0, 5, 0), Vec3<float>(1, 1, 1), Vec3<float>(0, 0, 0), "pinguin", {}, player));
  player->addComponent(new RotateToMouse(&player->getComponent<Transform>()->getRot(), engine.getInput(), player));
  player->addComponent(new PlayerMoveStateMachine(&player->getComponent<Transform>()->getPos(), &player->getComponent<Transform>()->getRot(), engine.getInput(), trickObject->getComponent<Trick>(), engine.deltaTime, player));
  player->addComponent(new CollisionComponent(false, new AABB(Vec3<float>(0, 0, 0), Vec3<float>(2.25f, 1.45, 2.25f)), player->getComponent<Transform>(), player));

  //create particle trail
  Object * particles = new Object({});
  ParticleTrail * particleComponet = new ParticleTrail(&player->getComponent<Transform>()->getRot(), &player->getComponent<Transform>()->getPos(), engine.deltaTime, particles, Vec3<float>(0, -0.9, 0.5));
  for (unsigned int i = 0; i < 500; i++) {
    Object * o = new Object({});
    o->addComponent(new Transform(Vec3<float>(0, 0, 0), Vec3<float>(0.05, 0.05, 0.05), Vec3<float>(), "cube", {"red"}, o));
    objects.push_back(o);
    particleComponet->addToInstance(o->getComponent<Transform>());
  }
  particles->addComponent(particleComponet);

  //create camera
  Object * camera = new Object({});
  camera->addComponent(new TextDebug<unsigned int>("fps: ", Vec2<float>(-1, 1), &engine.frames, camera));
  camera->addComponent(new FollowCamera(&player->getComponent<Transform>()->getPos(), camera, Vec3<float>(-50, 52, 50), Vec3<float>(35.2, 45, 0), Vec3<float>(1, 0, 1)));

  objects.push_back(camera);
  objects.push_back(instancedFence);
  objects.push_back(snowMan);
  objects.push_back(player);
  objects.push_back(particles);
  objects.push_back(trickObject);
  objects.push_back(scoreObject);

  CollisionModule * collisionModule = new CollisionModule(200, 4);
  // player->addComponent(new TextDebug<double>("dt: ", Vec2<float>(-1, 0.8), &engine.deltaTime, player));

  player->addComponent(new TextDebug<float>("->", Vec2<float>(-1, 0.8), &player->getComponent<Transform>()->getPos()[1], player));


  RenderModule * renderModule = new RenderModule(engine.getGeoLib(), engine.getMatLib(), engine.getShaderManger(), engine.getWidth(), engine.getHeight());
  renderModule->updateOrthoGraphic(2560, 1440, -1000.0f, 1000.0f);
  return new Scene(objects, {{collisionModule}, {renderModule}, {new UiRenderer("fonts/text", engine.getShaderManger(), engine.getHeight(), engine.getWidth())}});
}