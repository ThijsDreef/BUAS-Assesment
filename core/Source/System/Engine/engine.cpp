#include "System/Engine/engine.h"

Engine::Engine(std::string title, int iWidth, int iHeight, int bitDepth, bool fullScreen, double frameCap)
:
window(title.c_str(), iWidth, iHeight, bitDepth, fullScreen)
{
  width = iWidth;
  height = iHeight;
  this->frameCap = frameCap;
  loadResources();
  input = window.getInput();
  window.vsync(true);
}

Engine::Engine(double frameCap, int iWidth, int iHeight)
:
window("default", iWidth, iHeight, 32, true)
{
  width = iWidth;
  height = iHeight;
  this->frameCap = frameCap;
  loadResources();
  input = window.getInput();
  window.vsync(true);

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
    if (rsLine.substr(rsLine.size() - 4, rsLine.size()) == ".obj")
    {
      std::string name = rsLine.substr(rsLine.rfind("/") + 1);
      name = name.substr(0, name.size() - 4);
      std::cout << "parsing " << name << "\n";

      geometryLib.addGeometry(Geometry(rsLine.c_str(), name.c_str(), &materialLib));
    } 
    else if (rsLine.substr(rsLine.size() - 4, rsLine.size()) == ".png")
    {
      materialLib.addTexture(rsLine.substr(0, rsLine.size() - 4), new Texture(rsLine));
    }

  }
}

void Engine::start(Scene * start)
{
  running = true;
  scene.push(start);
  run();
  stop();
}

void Engine::run()
{
  double elapsedTime = 0;
  double inputResetTimer = 0;
  double fpsTimer;
  frames = 0;
  unsigned int currentFrames;
  while (!window.done && running)
  {
    auto start = std::chrono::system_clock::now();
    if (elapsedTime > frameCap)
    {
      window.handleMessages();
      scene.top()->update();
      elapsedTime -= frameCap;
      currentFrames ++;
      window.updateFrameBuffer();
      if (fpsTimer > 1000) {
        // log frames here or update them
        frames = currentFrames;
        currentFrames = 0;
        fpsTimer = 0;
      }
    }
    else
      std::this_thread::sleep_for(std::chrono::milliseconds((int)((frameCap - elapsedTime) * 1000)));
    if (inputResetTimer > 1.0 / 4.0)
    {
      window.updateInput();
      inputResetTimer -= 1.0 / 4.0;
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    elapsedTime += elapsed.count();
    fpsTimer += elapsed.count() * 1000;
    inputResetTimer += elapsedTime;
  }
  if (!window.done)
    window.killWindow();
}

void Engine::stop()
{
  for (unsigned int i = 0; i < scene.size(); i++)
  {
    delete scene.top();
    scene.pop();
  }
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

}

int Engine::getWidth()
{
  return width;
}

int Engine::getHeight()
{
  return height;
}
