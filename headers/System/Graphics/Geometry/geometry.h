#ifndef GEOMETRY__
#define GEOMETRY__
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include "Math/vec3.h"
#include "Math/vec4.h"
#include "System/Graphics/Geometry/materialLib.h"
#include "System/Graphics/Geometry/vertexFormat.h"
#include "Util/picoPNG.h"
#include "Util/rapidxml.hpp"

class Geometry
{
private:
	std::map<std::string, std::vector<float>> float_arrays;
  //sort indices per material
  std::vector<std::vector<unsigned int>> allIndices;
  //set indices with offset for large geo buffer
  std::vector<std::vector<unsigned int>> offsetIndices;
  int offset;
  void parseDaeControllers(rapidxml::xml_node<> * controllersNode);
  void parseDaeImages(rapidxml::xml_node<> * imageNode);
  void parseDaeMaterials(rapidxml::xml_node<> * materialNode);
  void parseDaeGeometry(rapidxml::xml_node<> * geometryNode);
  void parseDae(const std::string& fileName, MaterialLib& materialLib);
  void parseObj(const std::string& fileName, MaterialLib& materialLib);
public:
  std::vector<std::string> materials;
  std::string name;
  std::vector<VertexFormat> storedVertices;
  Geometry ();
  Geometry (const std::string & fileName, const std::string & name, MaterialLib & materialLib);
  void setIndiceOffset(int offset);
  const std::vector<std::string>& getMaterials();
  const std::vector<unsigned int>& getIndice(int group);
  virtual ~Geometry ();
};
#endif
