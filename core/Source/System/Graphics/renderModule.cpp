#include "System/Graphics/renderModule.h"

RenderModule::RenderModule(GeometryLib * geo, MaterialLib * mat, ShaderManager * shader)
{
  projection.perspectiveView(60, 1920.0f/1080.0f, 0.01, 100.0);
  camera.translateMatrix(Vec3<float>(0, 0, -2));
  geoLib = geo;
  matLib = mat;
  shaderManager = shader;
  geoLib->setUpBuffer();
  matLib->setUpBuffer();
  setUpFormat();
  glUseProgram(shaderManager->getShader("standard"));
}

RenderModule::~RenderModule()
{

}

void RenderModule::update()
{
  camera = camObject->getMatrix();
  bufferer.setBuffer(renderObjects, camera, projection);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, bufferer.getBufferId());
  std::map<std::string, std::vector<std::pair<unsigned int, Transform*>>> renderList;
  for (unsigned int i = 0; i < renderObjects.size(); i++)
  {
    if (renderObjects[i]->isDead())
    {
      renderObjects[i]->setRemoved();
      renderObjects.erase(renderObjects.begin() + i);
    }
    for (unsigned int j = 0; j < renderObjects[i]->materials.size(); j++)
    {
      if (j >= geoLib->getTotalGroups(renderObjects[i]->model))
        break;
      renderList[renderObjects[i]->materials[j]].push_back(std::pair<unsigned int, Transform*>(j, renderObjects[i]));
    }
  }
  for (auto const& i : renderList)
  {
    glBindBufferRange (GL_UNIFORM_BUFFER, 0, matLib->matBuffer.getBufferId(), matLib->getMaterialLoc(i.first), sizeof(Material));
    for (unsigned int j = 0; j < i.second.size(); j++)
    {
      glBindBufferRange(GL_SHADER_STORAGE_BUFFER, 1, bufferer.getBufferId(), i.second[j].second->bufferIndex * sizeof(MatrixBufferObject), sizeof(MatrixBufferObject));
      glDrawElements(GL_TRIANGLES, geoLib->getIndice(i.second[j].second->model, i.second[j].first).size(), GL_UNSIGNED_INT, &geoLib->getIndice(i.second[j].second->model, i.second[j].first)[0]);
    }
  }
}

void RenderModule::setUpFormat()
{
  // stream, buffer, offset, stride
  glBindVertexBuffer(0, geoLib->getGeoBufferId(), 0, 32);
  glEnableVertexAttribArray(0);
  glVertexAttribFormat(0, 3, GL_FLOAT, false,  0); // position
  glVertexAttribBinding(0, 0); // position -> stream 0
  glEnableVertexAttribArray(1);
  glVertexAttribFormat(1, 3, GL_FLOAT, false, 12); // normal
  glVertexAttribBinding(1, 0); // normal   -> stream 0
  glEnableVertexAttribArray(2);
  glVertexAttribFormat(2, 2, GL_FLOAT, false, 24); // texcoord
  glVertexAttribBinding(2, 0); // texcoord -> stream 0
}

Matrix<float> * RenderModule::getCameraMatrix()
{
  return &camera;
}

void RenderModule::updatePerspective(int width, int height, int fov, float near, float far)
{
  projection.perspectiveView(60, 1920.0f/1080.0f, 0.01, 10.0);
}

void RenderModule::addObject(Object * transform)
{
  Transform *  transObj = transform->getComponent<Transform>();
  if (transObj)
  {
    transObj->added();
    renderObjects.push_back(transObj);
  }
  Camera * cam = transform->getComponent<Camera>();
  if (cam) camObject = cam;
}
