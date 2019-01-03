#ifndef UIRENDERER__
#define UIRENDERER__

#include "System/module.h"
#include "System/Engine/EngineObjects/object.h"
#include "System/Graphics/Ui/uiText.h"
#include "System/Graphics/Resources/buffer.h"
#include "System/Graphics/Ui/font.h"
#include "System/Graphics/Shaders/shaderManager.h"




class UiRenderer : public Module
{
private:
  unsigned int vao;
  Font font;
  std::vector<UIText*> textObjects;
  void setupFormat();
  ShaderManager * shaderManager;
  unsigned int w, h;
public:
  UiRenderer(std::string fontFileName, ShaderManager * shader, unsigned int width, unsigned int height, int padding = 8);
  virtual ~UiRenderer();
  void renderText();
  void update();
  void addObject(Object * object);

};

#endif