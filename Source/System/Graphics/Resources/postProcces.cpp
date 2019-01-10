#include "System/Graphics/Resources/postProcces.h"

PostProcces::PostProcces(int width, int height, int screenWidth, int screenHeight, std::string postProccesShader, ShaderManager * shaderManager, GeometryLib * geometryLib) : fbo(width, height)
{
    w = width;
    h = height;
    sw = screenWidth;
    sh = screenHeight;
    shader = postProccesShader;
    this->shaderManager = shaderManager;
    geoLib = geometryLib;
	fbo.attach(GL_RGBA16F, GL_RGBA, GL_FLOAT, 0);
}

PostProcces::~PostProcces()
{

}

void PostProcces::draw(Fbo * previousFbo, bool lastDraw)
{
    if (lastDraw) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, sw, sh);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    } else {
        fbo.bind();
        glViewport(0, 0, w, h);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    if (previousFbo) glBindTextureUnit(10, previousFbo->getTextureIndex(0));
    glUseProgram(shaderManager->getShader(shader));
    setUniforms();
    std::vector<unsigned int> indice = geoLib->getIndice("quad", 0);
    glDrawElements(GL_TRIANGLES, indice.size(), GL_UNSIGNED_INT, &indice[0]);

}

void PostProcces::setUniforms()
{

}

Fbo * PostProcces::getFbo()
{
    return &fbo;
}