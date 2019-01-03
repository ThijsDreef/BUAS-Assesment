#include "System/Graphics/Geometry/geometryLib.h"

GeometryLib::GeometryLib() : geoBuffer("geometryBuffer", GL_ARRAY_BUFFER)
{

}

GeometryLib::~GeometryLib()
{

}

void GeometryLib::addGeometry(Geometry geometry)
{
  map[geometry.name] = geometry;
}

void GeometryLib::removeGeometry(std::string name)
{
  map.erase(name);
}

const Geometry& GeometryLib::getGeometry(std::string name)
{
  return map[name];
}

unsigned int GeometryLib::getTotalGroups(std::string geo)
{
  return map[geo].getMaterials().size();
}

const std::vector<int unsigned>& GeometryLib::getIndice(std::string geometry, int group)
{
  return map[geometry].getIndice(group);
}

void GeometryLib::setUpBuffer()
{
  unsigned int size = 0;
  int indiceOffset = 0;
  //get the total buffer size
  //and prepare a buffer
  std::vector<VertexFormat> allVertices;
  for (auto & i : map)
  {
    i.second.setIndiceOffset(allVertices.size());
    indiceOffset += i.second.storedVertices.size();
    allVertices.insert(allVertices.end(), i.second.storedVertices.begin(), i.second.storedVertices.end());
    size += i.second.storedVertices.size() * sizeof(VertexFormat);
  }
  //create a buffer with that size;
  geoBuffer.bufferData(size, &allVertices[0], GL_STATIC_DRAW);
  //print buffer size for fun !
  std::cout << "buffer size: in Bytes: " << size << "\n";
  std::cout << "buffer size: in KyloBytes: " << size / 1000.0<< "\n";
  std::cout << "buffer size: in MegaBytes: " << size / 1000000.0 << "\n";
}

unsigned int GeometryLib::getGeoBufferId()
{
  return geoBuffer.getBufferId();
}
