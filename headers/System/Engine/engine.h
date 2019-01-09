#ifndef ENGINE__
#define ENGINE__
#include <stack>
#include <thread> 
#include <chrono>
#include "System/Window/window.h"
#include "System/Graphics/Geometry/geometryLib.h"
#include "System/Graphics/Shaders/shaderManager.h"
#include "System/Engine/scene.h"
#include "Util/loadingUtils.h"
#include "System/Graphics/Geometry/materialLib.h"
#include "System/Input/input.h"
#include "System/Engine/options.h"

class Engine {
private:
  Window window;
  GeometryLib geometryLib;
  MaterialLib materialLib;
  ShaderManager shaderManager;
  Input * input;
  std::stack<Scene*> sceneStack;
  std::vector<Scene*> toBeDeletedScenes;
  void run();
  void stop();
  bool running;
  double frameCap;
  int width, height;
  void loadResources();
public:
  Options options;
  double deltaTime;
  double timeScale = 1;
  unsigned int frames;
  int getWidth();
  int getHeight();
  Engine (std::string title, int iWidth, int iHeight, int bitDepth, bool fullScreen, double frameCap);
  Engine (double frameCap, int iWidth, int iHeight);
  Engine (Options opts);
  void start(Scene * start);
  void pushScene(Scene * scene);
  Scene * popScene(bool clean);
  void quit();
  GeometryLib * getGeoLib();
  MaterialLib * getMatLib();
  ShaderManager * getShaderManger();
  Input * getInput();
  virtual ~Engine ();
};
#endif
