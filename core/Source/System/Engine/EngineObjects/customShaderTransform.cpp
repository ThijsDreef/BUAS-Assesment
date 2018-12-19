#include "System/Engine/EngineObjects/customShaderTransform.h"

CustomShaderTransform::CustomShaderTransform(std::string shader, std::string model, std::vector<std::string> materials, Object * object) : Transform(model, materials, object)
{
    this->shader = shader;
    shouldRenderDefault = false;
}

CustomShaderTransform::CustomShaderTransform (std::string shader, Vec3<float> pos, Vec3<float> scale, Vec3<float> rot, std::string model, std::vector<std::string> materials, Object * object) : 
Transform(pos, scale, rot, model, materials, object)
{
    shouldRenderDefault = false;
    this->shader = shader;
}

CustomShaderTransform::~CustomShaderTransform()
{

}


void CustomShaderTransform::onDraw(ShaderManager * shaderManager)
{

}

void CustomShaderTransform::onDrawExit(ShaderManager * shaderManager)
{

}

const std::string & CustomShaderTransform::getShader()
{
    return shader;
}

