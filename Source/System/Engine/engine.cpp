#include "System/Engine/engine.h"

Engine::Engine(std::string title, int iWidth, int iHeight, int bitDepth, bool fullScreen, double frameCap)
:
window(title.c_str(), iWidth, iHeight, bitDepth, fullScreen), options({})
{
  width = iWidth;
  height = iHeight;
  this->frameCap = frameCap;
  loadResources();
  input = window.getInput();
  window.vsync(false);
}

Engine::Engine(double frameCap, int iWidth, int iHeight)
:
window("default", iWidth, iHeight, 32, true), options({})
{
  width = iWidth;
  height = iHeight;
  this->frameCap = frameCap;
  loadResources();
  input = window.getInput();
  window.vsync(false);

}

Engine::Engine(Options opts) :
window(opts.getOption("title").c_str(), opts.getOptionI("width"), opts.getOptionI("height"), 32, opts.getOptionB("fullScreen")), options(opts)
{
  width = opts.getOptionI("width");
  height = opts.getOptionI("height");
  frameCap = 1.0 / opts.getOptionI("fpsLimit");
  loadResources();
  input = window.getInput();
  window.vsync(opts.getOptionB("vsync"));
}

void Engine::loadResources()
{
  //load resources.txt
  std::ifstream resourceFile("resource.txt");
  std::string rsLine;
  while (std::getline(resourceFile, rsLine))
  {
    //read lines that end with .obj
    //then load these files into the geolib
    std::string extension = rsLine.substr(rsLine.size() - 4, rsLine.size());
    if (extension == ".obj" || extension == ".dae")
    {
      std::string name = rsLine.substr(rsLine.rfind("/") + 1);
      name = name.substr(0, name.size() - 4);
      std::cout << "parsing " << name << "\n";

      geometryLib.addGeometry(Geometry(rsLine, name, materialLib));
    } 
  }
}

void Engine::start(Scene * start)
{
  running = true;
  geometryLib.setUpBuffer();
  materialLib.setUpBuffer();
  sceneStack.push(start);
  run();
  stop();
}

void Engine::run()
{
  double elapsedTime = 0;
  double inputResetTimer = 0;
  double fpsTimer = 0;
  frames = 0;
  unsigned int currentFrames = 0;
  while (!window.done && running)
  {
    for (unsigned int i = 0; i < toBeDeletedScenes.size(); i++) {
      delete toBeDeletedScenes[i];
    }
    toBeDeletedScenes.clear();
    auto start = std::chrono::system_clock::now();
    if (elapsedTime > frameCap)
    {
      deltaTime = elapsedTime * timeScale;
      window.handleMessages();
      sceneStack.top()->update();
      window.updateFrameBuffer();
      currentFrames ++;
      if (fpsTimer > 1) {
        frames = currentFrames;
        currentFrames = 0;
        fpsTimer = 0;
      }
      elapsedTime = 0;
    }
    else
      std::this_thread::sleep_for(std::chrono::milliseconds((int)((frameCap - elapsedTime) * 100.0)));
    if (inputResetTimer > 1.0 / 60.0)
    {
      window.updateInput();
      inputResetTimer = 0;
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    elapsedTime += elapsed.count();
    fpsTimer += elapsed.count();
    inputResetTimer += elapsed.count();;
  } 
  if (!window.done)
    window.killWindow();
}

void Engine::stop()
{
  for (unsigned int i = 0; i < sceneStack.size(); i++)
  {
    delete sceneStack.top();
    sceneStack.pop();
  }
}

void Engine::pushScene(Scene* scene)
{
  sceneStack.push(scene);
}

Scene * Engine::popScene(bool clean) 
{
  Scene * scene = sceneStack.top();
  sceneStack.pop();
  if (clean) toBeDeletedScenes.push_back(scene);
  return scene;
}

void Engine::quit()
{
  running = false;
}

GeometryLib * Engine::getGeoLib()
{
  return &geometryLib;
}

MaterialLib * Engine::getMatLib()
{
  return &materialLib;
}

ShaderManager * Engine::getShaderManger()
{
  return &shaderManager;
}

Input * Engine::getInput()
{
  return input;
}

Engine::~Engine()
{
  options.saveOptions("options.txt");
}

int Engine::getWidth()
{
  return width;
}

int Engine::getHeight()
{
  return height;
}
