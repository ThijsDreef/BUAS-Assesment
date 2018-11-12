#include "System/Engine/EngineObjects/transform.h"

Transform::Transform(std::string model, std::vector<std::string> materials, Object * object) : Component(object)
{
  this->model = model;
  this->materials = materials;
  pos = Vec3<float>(0, 0, 0);
  scale = Vec3<float>(1, 1, 1);
  rot = Vec3<float>(0, 0, 0);
}
Transform::~Transform()
{

}

Transform::Transform(Vec3<float> pos, Vec3<float> scale, Vec3<float> rot, std::string model, std::vector<std::string> materials, Object * object) : Component(object)
{
  this->model = model;
  this->materials = materials;
  this->pos = pos;
  this->scale = scale;
  this->rot = rot;
}

Vec3<float> & Transform::getPos()
{
  return pos;
}

Vec3<float> & Transform::getScale()
{
  return scale;
}

Vec3<float> & Transform::getRot()
{
  return rot;
}

MatrixBufferObject Transform::getBuffer(Matrix<float>& view, Matrix<float>& p)
{
  Matrix<float> mvp;
  Matrix<float> normal;
  Matrix<float> mv;
  Matrix<float> temp;
  Matrix<float> model;
  normal = normal.rotation(rot);
  temp.scaleMatrix(scale);
  mvp.translateMatrix(pos);
  mv = mvp.multiplyByMatrix(normal).multiplyByMatrix(temp);
  model = mv;
  mv = view.multiplyByMatrix(mv);
  mvp = p.multiplyByMatrix(mv);

  return MatrixBufferObject(mvp, mv, normal, model);
}

Matrix<float> Transform::getModelMatrix()
{
  Matrix<float> mvp;
  Matrix<float> normal;
  Matrix<float> temp;
  normal = normal.rotation(rot);
  temp.scaleMatrix(scale);
  mvp.translateMatrix(pos);
  return mvp.multiplyByMatrix(normal).multiplyByMatrix(temp);
}
