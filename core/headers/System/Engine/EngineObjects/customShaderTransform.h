#ifndef CUSTOMSHADERTRANSFORM__
#define CUSTOMSHADERTRANSFORM__

#include "System/Engine/EngineObjects/transform.h"
#include "System/Graphics/Shaders/shaderManager.h"

class CustomShaderTransform : public Transform 
{
protected:
  std::string shader;
public:
  const std::string & getShader();  
  CustomShaderTransform (std::string shader, std::string model, std::vector<std::string> materials, Object * object);
  CustomShaderTransform (std::string shader, Vec3<float> pos, Vec3<float> scale, Vec3<float> rot, std::string model, std::vector<std::string> materials, Object * object);
  virtual ~CustomShaderTransform();
  virtual void onDraw(ShaderManager * shaderManger);
  virtual void onDrawExit(ShaderManager * shaderManager);
};

#endif