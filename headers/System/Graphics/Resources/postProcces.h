#ifndef POSTPROCCES__
#define POSTPROCCES__

#include "System\Graphics\Geometry\geometryLib.h"
#include "System\Graphics\Shaders\shaderManager.h"
#include "System\Graphics\Resources\fbo.h"

class PostProcces 
{
private:
    Fbo fbo;
    int sw, sh, w, h;
    std::string shader;
    GeometryLib * geoLib;
    ShaderManager * shaderManager;
public:
    PostProcces(int width, int height, int screenWidth, int screenHeight, std::string postProccesShader, ShaderManager * shaderManager, GeometryLib * lib);
    virtual ~PostProcces();
    void draw(Fbo * previousFbo, bool lastDraw);
    Fbo * getFbo();
    virtual void setUniforms();
};

#endif