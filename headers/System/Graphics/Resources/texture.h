#include "System/Window/glew.h"
#include <iostream>
#include "Util/picoPNG.h"
#include "Util/loadingUtils.h"

#ifndef TEXTURE__
#define TEXTURE__ 

class Texture
{
private:
  unsigned long w;
  unsigned long h;
  unsigned int id;
  std::uint64_t residentId = 0;
  unsigned int iFormat;
  unsigned int format;
  unsigned int filter;
  unsigned int dataType;
  bool isResident = false;
  std::string name;
public:
  Texture (const std::string & fileName);
  Texture (int width, int height, const std::string textureName);
  Texture (int width, int height, void* data, std::string textureName);
  Texture (int width, int height, unsigned int internal, unsigned int format, void* data, std::string textureName);
  Texture (int width, int height, unsigned int internal, unsigned int format, unsigned int filter, unsigned int dataType, void* data, std::string textureName);
  void makeResident();
  void makeNonResident();
  void bufferData(int width, int height, std::string textureName, void* data);
  void bufferData(int width, int height, void* data);
  void bufferData(int width, int height, unsigned int internal, unsigned int format, void* data);
  void bufferData(int width, int height, unsigned int internal, unsigned int format, std::string textureName, void* data);
  void bind(unsigned int bindingPoint);
  void setFilter(unsigned int filter);
  std::uint64_t getResidentHandle();
  unsigned long getWidth();
  unsigned long getHeight();
  virtual ~Texture ();
  unsigned int getId();
};

#endif