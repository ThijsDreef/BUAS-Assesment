#ifndef RENDERMODULE__
#define RENDERMODULE__
#include "System/module.h"
#include "System/Graphics/Geometry/materialLib.h"
#include "System/Graphics/Geometry/geometryLib.h"
#include "System/Graphics/Geometry/matrixBufferer.h"
#include "System/Graphics/Shaders/shaderManager.h"
#include "Math/matrix.h"
#include "System/Graphics/Geometry/MatrixBufferObject.h"
#include "System/Graphics/Resources/buffer.h"
#include "System/Graphics/Resources/fbo.h"

#include "Util/util.h"
#include "System/Engine/EngineObjects/InstancedTransform.h"
#include "System/Engine/EngineObjects/transform.h"
#include "System/Engine/EngineObjects/object.h"
#include "System/Engine/EngineObjects/camera.h"
#include <iostream>
#include <math.h>

class RenderModule : public Module
{
private:
  unsigned int defaultVao;
  unsigned int instancedVao;
  GeometryLib * geoLib;
  MaterialLib * matLib;
  MatrixBufferer matBufferer;
  ShaderManager * shaderManager;
  Camera * camObject;
  int width, height;
  std::vector<Transform*> transforms;
  std::vector<InstancedTransform*> instancedTransforms;
  Matrix<float> projection;
  Matrix<float> camera;
  void setUpFormat();
  void setUpInstancedFormat();
  void bindInstance();
  void bindDefault();
  Fbo shadowFbo;
public:
  void updatePerspective(int width, int height, int fov, float near, float far);
  void updateOrthoGraphic(int width, int height, float near, float far);
  void update();
  void drawInstanced();
  void drawGeometry(std::vector<std::vector<std::pair<unsigned int, Transform*>>> & renderList, bool materials);
  Matrix<float> * getCameraMatrix();
  void addObject(Object * transform);
  RenderModule (GeometryLib * geo, MaterialLib * mat, ShaderManager * shader, int w, int h);
  virtual ~RenderModule ();
};
#endif
