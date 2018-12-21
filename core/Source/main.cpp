#include "System/Engine/engine.h"
#include "Game/Scenes/sceneFactory.h"


#include <iostream>

int main(int argc, char const *argv[])
{
  Engine engine("pingu on a mission", 1920, 1080, 32, true, 1/60.0);
  Texture * texture = new Texture("models/textures/iceTexture.png");
  engine.getMatLib()->addTexture("iceTexture", texture);
  Material mat;
  texture->makeResident();
  mat.texture = texture->getResidentHandle();
  mat.color = Vec4<float>(0.2, 0.2, 0.2, 1);

  Texture * water = new Texture("models/textures/water.png");
  engine.getMatLib()->addTexture("water", water);
  water->makeResident();
  Material m;
  m.texture = water->getResidentHandle();



  SceneFactory sceneFactory;
  
  engine.getMatLib()->addMaterial("blue", Material(Vec4<float>(0, 0, 1, 1)));
  engine.getMatLib()->addMaterial("lightBlue", Material(Vec4<float>(0.37, 0.61, 1, 1)));
  engine.getMatLib()->addMaterial("red", mat);
  engine.getMatLib()->addMaterial("water", m);


  engine.start(sceneFactory.createEndlessRunnerScene(engine));
  return 0;
}
