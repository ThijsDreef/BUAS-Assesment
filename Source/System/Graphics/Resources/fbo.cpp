#include "System/Graphics/Resources/fbo.h"
#include <iostream>
Fbo::Fbo(int width, int height)
{
  w = width;
  h = height;
  glGenFramebuffers(1, &id);
  glBindFramebuffer(GL_FRAMEBUFFER, id);
}

Fbo::~Fbo()
{
  for (unsigned int i = 0; i < textures.size(); i++)
    delete textures[i];
  if (renderBufferId) {
    glDeleteTextures(1, &renderBufferId);
  }
  glDeleteFramebuffers(1, &id);
}

void Fbo::attachDepth(int width, int height)
{
  bind();
  glGenTextures(1, &renderBufferId);
  glBindTexture(GL_TEXTURE_2D, renderBufferId);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, renderBufferId, 0);
}

unsigned int Fbo::getDepth()
{
  return renderBufferId;
}

unsigned int Fbo::getTextureIndex(unsigned int attachment)
{
  return textures[attachment]->getId();
}

void Fbo::attach(unsigned int internal, unsigned int format, unsigned int dataType, unsigned int bindingPoint)
{
  bind();
  textures.push_back(new Texture(w, h, internal, format, GL_NEAREST, dataType, 0, "fboTexture"));
  bindingPoints.push_back(bindingPoint);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + bindingPoint, GL_TEXTURE_2D, textures[textures.size() - 1]->getId(), 0);
  attachments.push_back(GL_COLOR_ATTACHMENT0 + bindingPoint);
  glDrawBuffers(attachments.size(), &attachments[0]);
}

void Fbo::attach(Texture * texture, unsigned int bindingPoint)
{
  textures.push_back(texture);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + bindingPoint, GL_TEXTURE_2D, textures[textures.size() - 1]->getId(), 0);
  attachments.push_back(GL_COLOR_ATTACHMENT0 + bindingPoint);
  glDrawBuffers(attachments.size(), &attachments[0]);
}

void Fbo::bind()
{
  glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void Fbo::prepareDraw()
{
  for (unsigned int i = 0; i < textures.size(); i++)
  {
    textures[i]->bind(bindingPoints[i]);
  }

}
