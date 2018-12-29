#ifndef WAVECUSTOMTRANSFORM__
#define WAVECUSTOMTRANSFORM__

#include "System/Engine/EngineObjects/customShaderTransform.h"

class WaveCustomTransform : public CustomShaderTransform
{
private:
  double & dt;
  float passedTime = 0.0f;
public:
  WaveCustomTransform(double & deltaTime, std::string shader, Vec3<float> pos, Vec3<float> scale, Vec3<float> rot, std::string model, std::vector<std::string> materials, Object * object);
  ~WaveCustomTransform();
  void onDraw(ShaderManager * shaderManger);
  void onDrawExit(ShaderManager * shaderManager);
};

#endif