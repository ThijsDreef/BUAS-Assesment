#ifndef TRANSFORM__
#define TRANSFORM__
#include "Math/matrix.h"
#include "System/Engine/EngineObjects/component.h"
#include "System/Engine/EngineObjects/object.h"
#include <string>
#include "System/Graphics/Geometry/matrixBufferObject.h"
#include <iostream>

class Transform : public Component
{
protected:
  Vec3<float> pos;
  Vec3<float> scale;
  Vec3<float> rot;
public:
  bool shouldRender = true;
  std::vector<std::string> materials;
  std::string model;
  unsigned int bufferIndex;
  Transform (std::string model, std::vector<std::string> materials, Object * object);
  Transform (Vec3<float> pos, Vec3<float> scale, Vec3<float> rot, std::string model, std::vector<std::string> materials, Object * object);
  Vec3<float> & getPos();
  Vec3<float> & getScale();
  Vec3<float> & getRot();
  bool castShadow = true;
  MatrixBufferObject getBuffer(Matrix<float>& view, Matrix<float>& p);
  Matrix<float> getModelMatrix();
  virtual ~Transform ();
};
#endif
