#ifndef GEOMETRYLIB__
#define GEOMETRYLIB__
#include "System/Graphics/Geometry/geometry.h"
#include "System/Graphics/Resources/buffer.h"
#include <string>
#include <map>

class GeometryLib
{
private:
  Buffer geoBuffer;
  std::map<std::string, Geometry> map;
public:
  void setUpBuffer();
  GeometryLib ();
  void addGeometry(Geometry geometry);
  void removeGeometry(std::string name);
  unsigned int getTotalGroups(std::string geo);
  const std::vector<unsigned int>& getIndice(std::string geometry, int group);
  const Geometry& getGeometry(std::string name);
  virtual ~GeometryLib ();
  unsigned int getGeoBufferId();
};
#endif
