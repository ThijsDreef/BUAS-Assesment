#include "System/Engine/engine.h"
#include "Game/Scenes/sceneFactory.h"


#include <iostream>

int main(int argc, char const *argv[])
{
  Engine engine("pingu on a mission", 2560, 1440, 32, true, 1/60.0f);
  Texture * texture = new Texture("models/textures/iceTexture.png");
  engine.getMatLib()->addTexture("iceTexture", texture);
  Material mat;
  mat.texture = texture->getId();
  mat.color = Vec4<float>(0, 0, 1, 1);

  SceneFactory sceneFactory;
  
  engine.getMatLib()->addMaterial("blue", Material(Vec4<float>(0, 0, 1, 1)));
  engine.getMatLib()->addMaterial("lightBlue", Material(Vec4<float>(0.37, 0.61, 1, 1)));
  engine.getMatLib()->addMaterial("red", mat);

  engine.start(sceneFactory.createEndlessRunnerScene(engine));
  return 0;
}
