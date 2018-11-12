#include "System/Graphics/Geometry/matrixBufferer.h"

MatrixBufferer::MatrixBufferer() : matrixBuffer("matrix", GL_SHADER_STORAGE_BUFFER)
{
  bufferObjects.reserve(maxSize);
  matrixBuffer.bufferData(sizeof(MatrixBufferObject) * maxSize, 0, GL_DYNAMIC_DRAW);
}

void MatrixBufferer::setBuffer(std::vector<Transform*> & transforms, Matrix<float>& view, Matrix<float>& perspective)
{
  bool resized = false;
  if (transforms.size() > maxSize)
  {
    bufferObjects.reserve(transforms.size());
    maxSize = transforms.size();
    resized = true;
  }
  for (unsigned int i = 0; i < transforms.size(); i++)
  {
    bufferObjects[i] = transforms[i]->getBuffer(view, perspective);
    transforms[i]->bufferIndex = i;
  }
  if (resized)
    matrixBuffer.bufferData(sizeof(MatrixBufferObject) * bufferObjects.size(), &bufferObjects[0], GL_DYNAMIC_DRAW);
  else
    matrixBuffer.bufferSubData(0, sizeof(MatrixBufferObject) * transforms.size(), &bufferObjects[0]);
}

int MatrixBufferer::getBufferId()
{
  return matrixBuffer.getBufferId();
}

MatrixBufferer::~MatrixBufferer()
{

}
