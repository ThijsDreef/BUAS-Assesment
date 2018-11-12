#include "System/Graphics/Resources/texture.h"

Texture::Texture(const std::string & fileName)
{
  std::vector<unsigned char> buffer, image;
  UtilLoader::loadFile(buffer, fileName);
  //w and h members are set here
  int error = decodePNG(image, w, h, buffer.empty() ? 0 : &buffer[0], (unsigned long)buffer.size());  
  name = fileName;
  iFormat = GL_RGBA;
  format = GL_RGBA;

  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, iFormat, w, h, 0, format, GL_UNSIGNED_BYTE, &image[0]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::Texture(int width, int height, std::string textureName)
{
  w = width;
  h = height;
  name = textureName;
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::Texture(int width, int height, unsigned int internal, unsigned int format, void* data, std::string textureName)
{
  w = width;
  h = height;
  name = textureName;
  iFormat = internal;
  this->format = format;
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, internal, width, height, 0, format, GL_FLOAT, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::Texture(int width, int height, unsigned int internal, unsigned int format, unsigned int filter, unsigned int dataType, void* data, std::string textureName)
{
  w = width;
  h = height;
  name = textureName;
  iFormat = internal;
  this->format = format;
  this->filter = filter;
  this->dataType = dataType;
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, internal, width, height, 0, format, dataType, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
}

Texture::Texture(int width, int height, void* data, std::string textureName)
{
  w = width;
  h = height;
  name = textureName;
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::~Texture()
{

}

void Texture::bufferData(int width, int height, std::string textureName, void* data)
{
  name = textureName;
  bufferData(width, height, data);
}

void Texture::bufferData(int width, int height, unsigned int internal, unsigned int format, void* data)
{
  iFormat = internal;
  this->format = format;
  bufferData(width, height, data);
}

void Texture::bufferData(int width, int height, unsigned int internal, unsigned int format, std::string textureName, void* data)
{
  name = textureName;
  bufferData(width, height, internal, format, data);
}
void Texture::bufferData(int width, int height, void* data)
{
  w = width;
  h = height;
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, iFormat, width, height, 0, format, GL_FLOAT, data);
}

void Texture::setFilter(unsigned int filter)
{
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
}

void Texture::bind(unsigned int bindingPoint)
{
  glActiveTexture(GL_TEXTURE0 + bindingPoint);
  glBindTexture(GL_TEXTURE_2D, id);
}

unsigned long Texture::getWidth() 
{
  return w;
}

unsigned long Texture::getHeight()
{
  return h;
}

unsigned int Texture::getId()
{
  return id;
}
