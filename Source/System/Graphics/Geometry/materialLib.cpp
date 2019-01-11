#include "System/Graphics/Geometry/materialLib.h"

MaterialLib::MaterialLib() : matBuffer("matBuffer", GL_UNIFORM_BUFFER)
{
  map["Material"] = Material();
}

void MaterialLib::addMaterial(const std::string& name, Material mat)
{
  if (map.find(name) != map.end())
    std::cout << "warning at " << name << " material collision \n";
  map[name] = mat;
}

void MaterialLib::addTexture(const std::string name, Texture * texture)
{
  if (map.find(name) != map.end())
    std::cout << "warning at " << name << " texture overWrite \n";
  textures[name] = texture;
}

void MaterialLib::removeMaterial(const std::string& name)
{
  map.erase(name);
}

Texture * MaterialLib::getTexture(const std::string name)
{
  return textures[name];
}

Material& MaterialLib::getMaterial(const std::string& name)
{
  return map[name];
}

Material& MaterialLib::getMaterial(const unsigned int id)
{
  return map[byId[id]];
}

unsigned int MaterialLib::getMaterialId(const std::string & name)
{
  return loc[name] / sizeof(Material);
}

unsigned int MaterialLib::getMaterialLoc(const std::string& name)
{
  return loc[name];
}


void MaterialLib::setUpBuffer()
{
  unsigned int size = 0;
  //get the total buffer size
  std::vector<Material> allMats;
  byId.clear();
  //and prepare a buffer
  for (auto & i : map)
  { 
    byId.push_back(i.first);
    loc[i.first] = size;
    allMats.push_back(i.second);
    size += sizeof(Material);
  }
  //create a buffer with that size;
  matBuffer.bufferData(size, &allMats[0], GL_STATIC_DRAW);
  //print buffer size for fun !
  std::cout << "buffer size: in Bytes: " << size << "\n";
  std::cout << "buffer size: in KyloBytes: " << size / 1000.0<< "\n";
  std::cout << "buffer size: in MegaBytes: " << size / 1000000.0 << "\n";
  glBindBufferBase(GL_UNIFORM_BUFFER, 0,matBuffer.getBufferId());
  glBindBufferRange (GL_UNIFORM_BUFFER, 0, matBuffer.getBufferId(), 16, 16);


}	

MaterialLib::~MaterialLib()
{
  for (auto & i : textures)
  {
	if (!i.second) continue;
    unsigned int id = i.second->getId();
    glDeleteTextures(1, &id);
    delete i.second;
  }
}
