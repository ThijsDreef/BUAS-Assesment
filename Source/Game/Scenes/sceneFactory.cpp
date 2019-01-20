#include "Game/Scenes/sceneFactory.h"

SceneFactory::SceneFactory()
{

}

SceneFactory::~SceneFactory()
{

}

Scene * SceneFactory::createScene(const std::string & sceneName, Engine & engine)
{
  if (sceneName == "endlessRunnerScene") {
    return createEndlessRunnerScene(engine);
  } else if (sceneName == "menu") {
    return createMainMenuScene(engine);
  } else 
    return 0;
}

Scene * SceneFactory::createMainMenuScene(Engine & engine)
{

  std::vector<Object*> objects;

  Object * sea = new Object({});
  sea->addComponent(new WaveCustomTransform(engine.deltaTime, "seaShader", Vec3<float>(0, -4, 0), Vec3<float>(5, 4, 5), Vec3<float>(), "sea", {"water"}, sea));
  sea->getComponent<WaveCustomTransform>()->castShadow = false;

  objects.push_back(sea);

  Object * pinguin = new Object({});
  pinguin->addComponent(new Transform(Vec3<float>(0, 2, 0), Vec3<float>(1, 1, 1), Vec3<float>(0, 90, 0), "pinguin", {}, pinguin));
  objects.push_back(pinguin);

  Object * ice = new Object({});
  ice->addComponent(new Transform(Vec3<float>(0, -5, 0), Vec3<float>(5, 5, 5), Vec3<float>(), "berg", {"ice"}, ice));
  objects.push_back(ice);
  
  for (int x = 0; x < 2; x++) { 
    Object * shark = new Object({});
    shark->addComponent(new Transform(Vec3<float>(-15 + x * 30, -10, -5), Vec3<float>(1, 1, 1), Vec3<float>(0, 45, 0), "shark", {}, shark));
    shark->addComponent(new SharkDispatch(Vec3<float>(0, 0, 10), engine.deltaTime, shark));
    shark->addComponent(new SharkStateMachine(engine.deltaTime, shark));
    objects.push_back(shark);
  }

  Object * camera = new Object({});
  //this needs refractoring this is a memory leak
  camera->addComponent(new FollowCamera(new Vec3<float>(), camera, Vec3<float>(-50, 52, 50), Vec3<float>(35.2, 45, 0), Vec3<float>(1, 0, 1)));
  objects.push_back(camera);

  Object * title = new Object({});
  title->addComponent(new UIText("Pinguin on a Mission", Vec2<float>(-1, 0.8), title));
  title->getComponent<UIText>()->shouldCenter = true;
  objects.push_back(title);

  Object * spaceToStart = new Object({});
  spaceToStart->addComponent(new UIText("press space to start", Vec2<float>(0, -0.6), spaceToStart));
  spaceToStart->addComponent(new LoadSceneEvent("start", "endlessRunnerScene", spaceToStart, this, engine, spaceToStart));
  spaceToStart->addComponent(new EventOnKey({KeyEvent(32, "start")}, engine.getInput(), spaceToStart));
  spaceToStart->getComponent<UIText>()->shouldCenter = true;
  objects.push_back(spaceToStart);



  RenderModule * renderModule = new RenderModule(engine.getGeoLib(), engine.getMatLib(), engine.getShaderManger(), engine.getWidth(), engine.getHeight());
  renderModule->updateOrthoGraphic(engine.getWidth(), engine.getHeight(), -1000.0f, 1000.0f);

  if (engine.options.getOptionI("lutNumber") > 0) {
    ColorGrade * colorGrade = new ColorGrade(engine.getMatLib()->getTexture(engine.options.getOption("currentLut")), engine.getWidth(), engine.getHeight(), engine.getWidth(), engine.getHeight(), engine.getShaderManger(), engine.getGeoLib());
    Object * lutObject = new Object({});
    lutObject->addComponent(new EventOnKey({KeyEvent(68, "incrementLut"), KeyEvent(65, "decrementLut")}, engine.getInput(), lutObject));
    lutObject->addComponent(new ChangeLutEvent(Vec2<float>(-0.9, 0.9), *colorGrade, engine, lutObject));
    objects.push_back(lutObject);
    renderModule->addToPostProccesStack(colorGrade);
  }
  return new Scene(objects, {
    {renderModule},
    {new UiRenderer("fonts/text", engine.getShaderManger(), engine.getHeight(), engine.getWidth())}
  });
}

Scene * SceneFactory::createEndlessRunnerScene(Engine & engine)
{
  std::vector<Object*> objects;

  Object* autoScroller = new Object({});
  autoScroller->addComponent(new Score(Vec2<float>(0, 0.95), autoScroller));
  autoScroller->getComponent<Score>()->shouldCenter = true;

  autoScroller->addComponent(new AutoScroller(Vec3<float>(60, -5, 0), Vec3<float>(-30 * 2, 0, 0), Vec3<float>(-7, 0, 0), engine.deltaTime, autoScroller));
  autoScroller->addComponent(new ChunkSpawner(autoScroller->getComponent<AutoScroller>(), autoScroller));
  objects.push_back(autoScroller);

  Object * player = new Object({});
  player->addComponent(new Transform(Vec3<float>(0, 3, 0), Vec3<float>(1, 1, 1), Vec3<float>(), "pinguin", {}, player));
  player->addComponent(new PlayerMovement(&player->getComponent<Transform>()->getPos(), &player->getComponent<Transform>()->getRot(), engine.getInput(), engine.deltaTime, player));
  player->addComponent(new CollisionComponent(false, new AABB(Vec3<float>(0, 0, 0), Vec3<float>(2, 2, 2)), player->getComponent<Transform>(), player, "player"));
  player->addComponent(new DeathWall(-50, player));
  player->addComponent(new LoadSceneEvent("dead", "menu", player, this, engine, player));
  
  autoScroller->getComponent<AutoScroller>()->addTransform(player->getComponent<Transform>());
  objects.push_back(player);

  for (int i = 0; i < 4; i++) {
    Object * shark = new Object({});
    shark->addComponent(new Transform(Vec3<float>(15 + i * 30, -10, 15), Vec3<float>(1, 1, 1), Vec3<float>(0, 0, 0), "shark", {}, shark));
    shark->addComponent(new SharkDispatch(Vec3<float>(0, 0, 30), engine.deltaTime, shark));
    shark->addComponent(new SharkStateMachine(engine.deltaTime, shark));
    shark->addComponent(new PushOnCollision(Vec3<float>(0, 0, -1), &shark->getComponent<Transform>()->getRot(), "player", shark));
    shark->addComponent(new CollisionComponent(false, new AABB(Vec3<float>(0, 0, 0), Vec3<float>(2, 2.5, 3)), shark->getComponent<Transform>(), shark, "shark"));
    autoScroller->getComponent<AutoScroller>()->addTransform(shark->getComponent<Transform>());
    autoScroller->getComponent<AutoScroller>()->addScrollingVector(&shark->getComponent<SharkStateMachine>()->getOriginalFromJump());
    autoScroller->getComponent<AutoScroller>()->addScrollingVector(&shark->getComponent<SharkStateMachine>()->getTarget());
    shark->getComponent<SharkStateMachine>()->setMoveScale(&autoScroller->getComponent<AutoScroller>()->getMoveScale());
    objects.push_back(shark);
  }


  Object * particles = new Object({});
  ParticleTrail * particleComponet = new ParticleTrail(&player->getComponent<Transform>()->getRot(), &player->getComponent<Transform>()->getPos(), engine.deltaTime, particles, Vec3<float>(0, -0.9, 0.5));
  for (unsigned int i = 0; i < 25; i++) {
    Object * o = new Object({});
    o->addComponent(new Transform(Vec3<float>(0, 0, 0), Vec3<float>(0.05, 0.05, 0.05), Vec3<float>(), "ice", {"ice"}, o));
    autoScroller->getComponent<AutoScroller>()->addTransform(o->getComponent<Transform>());
    objects.push_back(o);
    particleComponet->addToInstance(o->getComponent<Transform>());
  }
  particles->addComponent(particleComponet);
  objects.push_back(particles);

  Object * pause = new Object({});
  pause->addComponent(new EventOnKey({KeyEvent(27, "pause"), KeyEvent(32, "unPause"), KeyEvent(68, "unPause"), KeyEvent(87, "unPause"), KeyEvent(65, "unPause"), KeyEvent(83, "unPause")}, engine.getInput(), pause));
  pause->addComponent(new PauseEvent(pause, engine, pause));

  objects.push_back(pause);


  Object * particleSystem = new Object({});
  particleSystem->addComponent(new ExplosionEvent(particleSystem, engine.deltaTime, particleSystem));

  for (int i = 0; i < 50; i++) {
    Object * p = new Object({});
    p->addComponent(new Transform("coin", {"coin"}, p));
    autoScroller->getComponent<AutoScroller>()->addTransform(p->getComponent<Transform>());
    particleSystem->getComponent<ParticleSystem>()->addToInstance(p->getComponent<Transform>());
    objects.push_back(p);
  }

  objects.push_back(particleSystem);

  for (int i = 0; i < 4; i++) {
    Object * platform = new Object({});
    platform->addComponent(new Transform(Vec3<float>(30 * i, 0, 0), Vec3<float>(10, 8, 10), Vec3<float>(), "berg", {"ice"}, platform));
    platform->addComponent(new CollisionComponent(false, new AABB(Vec3<float>(0, 0, 0), Vec3<float>(10, 8, 10)), platform->getComponent<Transform>(), platform, "ground"));
    platform->addComponent(new SinkAble(&platform->getComponent<Transform>()->getPos(), -5, engine.deltaTime, platform));
    platform->getComponent<CollisionComponent>()->getCollider()->isMoveAble = false;
    platform->addComponent(new ScaleOnRespawn(Vec3<float> (4, 8, 4), Vec3<float>(8, 8, 8), platform, platform));
    autoScroller->getComponent<AutoScroller>()->addTransform(platform->getComponent<Transform>());
    
    Object * coin = new Object({});
    coin->addComponent(new Transform(Vec3<float>(15 + 30 * i, 12.5f, 0), Vec3<float>(1, 1, 1), Vec3<float>(0, 0, 90), "coin", {"coin"}, coin));
    coin->addComponent(new CollisionComponent(false, new AABB(Vec3<float>(), Vec3<float>(1, 1, 1)), coin->getComponent<Transform>(), coin));
    coin->getComponent<CollisionComponent>()->getCollider()->isTrigger = true;
    coin->addComponent(new CoinOnCollision(engine.deltaTime, coin));
    coin->addComponent(new RotateComponent(coin->getComponent<Transform>()->getRot(), Vec3<float>(0, 360, 0), engine.deltaTime, coin));
    coin->subscribe("explosion", particleSystem->getComponent<ExplosionEvent>());
	  coin->subscribe("addScore", autoScroller->getComponent<Score>());
    autoScroller->getComponent<AutoScroller>()->addTransform(coin->getComponent<Transform>());

    objects.push_back(platform);
    objects.push_back(coin);

  }

  Object * sea = new Object({});
  sea->addComponent(new WaveCustomTransform(engine.deltaTime, "seaShader", Vec3<float>(0, -4, 0), Vec3<float>(5, 4, 5), Vec3<float>(), "sea", {"water"}, sea));
  sea->getComponent<WaveCustomTransform>()->setTimeScale(&autoScroller->getComponent<AutoScroller>()->getMoveScale());
  sea->getComponent<WaveCustomTransform>()->castShadow = false;
  objects.push_back(sea);

  Object * camera = new Object({});
  //this needs refractoring this is a memory leak
  camera->addComponent(new FollowCamera(new Vec3<float>(), camera, Vec3<float>(-50, 52, 50), Vec3<float>(35.2, 45, 0), Vec3<float>(1, 0, 1)));
  objects.push_back(camera);



  RenderModule * renderModule = new RenderModule(engine.getGeoLib(), engine.getMatLib(), engine.getShaderManger(), engine.getWidth(), engine.getHeight());
  renderModule->updateOrthoGraphic(engine.getWidth(), engine.getHeight(), -1000.0f, 1000.0f); 
  if (engine.options.getOptionI("lutNumber") > 0) {
    renderModule->addToPostProccesStack(new ColorGrade(engine.getMatLib()->getTexture("lut" + engine.options.getOption("currentLut")), engine.getWidth(), engine.getHeight(), engine.getWidth(), engine.getHeight(), engine.getShaderManger(), engine.getGeoLib()));
  }

  return new Scene(objects, {
    {new CollisionModule(200, 4)},
    {renderModule},
    {new UiRenderer("fonts/text", engine.getShaderManger(), engine.getHeight(), engine.getWidth())}
  });
}
