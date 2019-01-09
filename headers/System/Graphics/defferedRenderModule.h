#ifndef DEFFEREDRENDERMODULE__
#define DEFFEREDRENDERMODULE__
#include "System/module.h"
#include "System/Graphics/Geometry/materialLib.h"
#include "System/Graphics/Geometry/geometryLib.h"
#include "System/Graphics/Geometry/matrixBufferer.h"
#include "System/Graphics/Shaders/shaderManager.h"
#include "System/Graphics/Geometry/MatrixBufferObject.h"
#include "Math/matrix.h"
#include "System/Graphics/Resources/buffer.h"
#include "Util/loadingUtils.h"
#include "System/Engine/EngineObjects/transform.h"
#include "System/Window/glew.h"
#include "System/Engine/EngineObjects/object.h"
#include <math.h>
#include <utility>
#include "System/Engine/EngineObjects/camera.h"
#include "System/Engine/EngineObjects/InstancedTransform.h"
#include "System/Graphics/Resources/fbo.h"

class DefferedRenderModule : public Module
{
private:
  unsigned int defaultVao;
  unsigned int instancedVao;
  GeometryLib * geoLib;
  MaterialLib * matLib;
  MatrixBufferer matBufferer;
  ShaderManager * shaderManager;
  std::vector<InstancedTransform*> instancedTransforms;
  std::vector<Transform*> transforms;
  Fbo renderFbo;
  Fbo shadowFbo;
  Camera * camObject;
  Matrix<float> camera;
  Matrix<float> projection;
  void setUpFormat();
  void setUpInstancedFormat();
  void bindInstance();
  void bindDefault();
  int w, h;
public:
  DefferedRenderModule (GeometryLib * geo, MaterialLib * mat, ShaderManager * shader, int width, int height);
  virtual ~DefferedRenderModule ();
  void update();
  void drawInstanced();
  void drawGeometry(std::vector<std::vector<std::pair<unsigned int, Transform*>>> & renderList, bool materials);
  void updatePerspective(int width, int height, int fov, float near, float far);
  void updateOrthoGraphic(int width, int height, float near, float far);
  void addObject(Object * object);
  Matrix<float> * getCameraMatrix();
};
#endif
