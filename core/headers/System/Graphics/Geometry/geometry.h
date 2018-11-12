#ifndef GEOMETRY__
#define GEOMETRY__
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include "Math/vec3.h"
#include "Math/vec4.h"
#include "System/Graphics/Geometry/materialLib.h"
#include "System/Graphics/Geometry/vertexFormat.h"
#include "Util/picoPNG.h"

class Geometry
{
private:
  //sort indices per material
  std::vector<std::vector<unsigned int>> allIndices;
  //set indices with offset for large geo buffer
  std::vector<std::vector<unsigned int>> offsetIndices;
  int offset;
  bool parseObj(const std::string& fileName, MaterialLib * materialLib);
public:
  std::vector<std::string> materials;
  std::string name;
  std::vector<VertexFormat> storedVertices;
  Geometry ();
  Geometry (const char * fileName, const char* name, MaterialLib * materialLib);
  void setIndiceOffset(int offset);
  const std::vector<std::string>& getMaterials();
  const std::vector<unsigned int>& getIndice(int group);
  virtual ~Geometry ();
};
#endif
