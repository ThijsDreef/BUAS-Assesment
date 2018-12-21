#include "Game/Object/waveCustomTransform.h"

WaveCustomTransform::WaveCustomTransform(double & deltaTime, std::string shader, Vec3<float> pos, Vec3<float> scale, Vec3<float> rot, std::string model, std::vector<std::string> materials, Object * object) : 
CustomShaderTransform(shader, pos, scale, rot, model, materials, object), dt(deltaTime)
{

}

WaveCustomTransform::~WaveCustomTransform()
{

}

void WaveCustomTransform::onDraw(ShaderManager * shaderManger)
{
  glUniform1f(shaderManger->uniformLocation(shader, "uTime"), passedTime * 0.2);
  glUniform1f(shaderManger->uniformLocation(shader, "uTexScroll"), passedTime * 0.08);

  passedTime += dt;
}

void WaveCustomTransform::onDrawExit(ShaderManager * shaderManger)
{

}