#ifndef MATERIALLIB__
#define MATERIALLIB__

#include "System/Graphics/Geometry/material.h"
#include <vector>
#include <map>
#include "System/Graphics/Resources/buffer.h"
#include <string>
#include "System/Graphics/Resources/texture.h"

class MaterialLib
{
private:
  std::map<std::string, Texture*> textures;
  std::map<std::string, Material> map;
  std::map<std::string, unsigned int> loc;
  std::vector<std::string> byId;
public:
  Buffer matBuffer;

  MaterialLib ();
  void setUpBuffer();
  void addMaterial(const std::string& name, Material mat);
  void removeMaterial(const std::string& name);
  unsigned int getMaterialId(const std::string& name);
  unsigned int getMaterialLoc(const std::string& name);
  void addTexture(const std::string name, Texture * texture);
  Texture * getTexture(const std::string name);
  void removeTexture(const std::string name);
  Material& getMaterial(const std::string& name);
  Material& getMaterial(const unsigned int id);
  virtual ~MaterialLib ();
};

#endif
