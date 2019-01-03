#ifndef MATRIXBUFFEROBJECT__
#define MATRIXBUFFEROBJECT__
#include "Math/matrix.h"
struct MatrixBufferObject
{
  Matrix<float> mvp;
  Matrix<float> modelView;
  Matrix<float> normal;
  Matrix<float> model;
  char pad[64];
  MatrixBufferObject(Matrix<float>& mvp, Matrix<float>& modelView, Matrix<float>& normal, Matrix<float> & model)
  {
    this->mvp = mvp;
    this->modelView = modelView;
    this->normal = normal;
    this->model = model;
  }
};
#endif
