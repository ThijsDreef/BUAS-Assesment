
#include "System/Engine/engine.h"
#include "Game/Scenes/sceneFactory.h"
#include "Util/loadingUtils.h"
#include "Util/platformUtils.h"



int main(int argc, char const *argv[])
{
  Options opts = Options({
    OptionData("title", "pingu On a Mission"),
    OptionData("width", "1920"),
    OptionData("height", "1080"),
    OptionData("fullScreen", "0"),
    OptionData("fpsLimit", "60"),
    OptionData("vsync", "true"),  
  });


  opts.loadOptions("options.txt");
  Engine engine(opts);

  std::vector<std::string> files;
  PlatformUtils::readDirectory("shaders/postProccesing/luts", files);
  int lutNumber = 0;
  for (unsigned int i = 0; i < files.size(); i++) {
    if (files[i].length() > 4 && files[i].substr(files[i].length() - 4, files[i].length()) == ".png") {
      engine.getMatLib()->addTexture("lut" + std::to_string(lutNumber), new Texture("shaders/postProccesing/luts/" + files[i]));
      lutNumber++;
    }
  }
  engine.options.setOption(OptionData("lutNumber", std::to_string(lutNumber)));
  engine.options.setOption(OptionData("currentLut", "1"));

  Texture * lut = new Texture("shaders/postProccesing/luts/sepia.png");
  engine.getMatLib()->addTexture("defaultLut", lut);

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

  engine.getShaderManger()->createShaderProgram("shaders/forward/custom/standard.vert", "shaders/forward/custom/standard.frag", "seaShader");
  engine.getShaderManger()->createShaderProgram("shaders/postProccesing/default.vert", "shaders/postProccesing/colorGrade.frag", "colorGrade");


  SceneFactory sceneFactory;
  
  engine.getMatLib()->addMaterial("ice", mat);
  engine.getMatLib()->addMaterial("water", m);


  engine.start(sceneFactory.createMainMenuScene(engine));
  return 0;
}
