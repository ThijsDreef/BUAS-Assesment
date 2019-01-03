#include "System/Engine/engine.h"
#include "Game/Scenes/sceneFactory.h"

int main(int argc, char const *argv[])
{
  Engine engine("pingu on a mission", 1920 * 0.5, 1080 * 0.5, 32, false, 1/60.0);
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
  m.color = Vec4<float>(0.2, 0.2, 0.2, 1);

  engine.getShaderManger()->createShaderProgram("shaders/forward/custom/standard.vert", "shaders/forward/custom/standard.frag", "redStandard");



  SceneFactory sceneFactory;
  
  engine.getMatLib()->addMaterial("blue", Material(Vec4<float>(0, 0, 1, 1)));
  engine.getMatLib()->addMaterial("lightBlue", Material(Vec4<float>(0.37, 0.61, 1, 1)));
  engine.getMatLib()->addMaterial("red", mat);
  engine.getMatLib()->addMaterial("water", m);


  engine.start(sceneFactory.createMainMenuScene(engine));
  return 0;
}
