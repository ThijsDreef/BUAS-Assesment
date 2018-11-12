#ifndef CAMERA__
#define CAMERA__
#include "System/Engine/EngineObjects/component.h"
#include "Math/matrix.h"
class Camera : public Component
{
protected:
  Matrix<float> camera;
public:
  Camera (Object * object);
  virtual Matrix<float> & getMatrix();
  virtual ~Camera ();
};
#endif
