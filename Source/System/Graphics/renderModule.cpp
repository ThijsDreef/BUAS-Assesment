#include "System/Graphics/renderModule.h"

RenderModule::RenderModule(GeometryLib * geo, MaterialLib * mat, ShaderManager * shader, int w, int h) : shadowFbo(4096, 4096), storage(w, h)
{
  glGenVertexArrays(1, &defaultVao);
  glGenVertexArrays(1, &instancedVao);
  projection.perspectiveView(60, 1920.0f/1080.0f, 0.01, 100.0);
  camera.translateMatrix(Vec3<float>(0, 0, -2));
  geoLib = geo;
  matLib = mat;
  width = w;
  height = h;
  shaderManager = shader;
  shadowFbo.bind();
  shadowFbo.attachDepth(4096, 4096);
  setUpFormat();
  setUpInstancedFormat();
  storage.attach(GL_RGBA16F, GL_RGBA, GL_FLOAT, 0);
  storage.attachDepth(w, h);

  shaderManager->createShaderProgram("shaders/forward/standard.vert", "shaders/forward/standard.frag", "standard");
  shaderManager->createShaderProgram("shaders/forward/instanced.vert", "shaders/forward/instanced.frag", "instanced");
  shaderManager->createShaderProgram("shaders/shadow/directionalLightInstanced.vert", "shaders/shadow/directionalLightInstanced.frag", "directionalLightInstanced");
  shaderManager->createShaderProgram("shaders/shadow/directionalLight.vert", "shaders/shadow/directionalLight.frag", "directionalLight");
}

void RenderModule::addToPostProccesStack(PostProcces * post)
{
  postProccesStack.push_back(post);
}

RenderModule::~RenderModule()
{
  glDeleteVertexArrays(1, &defaultVao);
  glDeleteVertexArrays(1, &instancedVao);
  for (unsigned int i = 0; i < postProccesStack.size(); i++)
    delete postProccesStack[i];

}

void RenderModule::update()
{
  camera = camObject->getMatrix();
  matBufferer.setBuffer(transforms, camera, projection);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, matBufferer.getBufferId());

  //TODO REFRACTOR THIS
  std::vector<std::vector<std::pair<unsigned int, Transform*>>> renderList;
  for (unsigned int i = 0; i < transforms.size(); i++)
  {
    if (transforms[i]->isDead())
    {
      transforms[i]->setRemoved();
      transforms.erase(transforms.begin() + i);
    }
    for (unsigned int j = 0; j < transforms[i]->materials.size(); j++)
    {
      if (j >= geoLib->getTotalGroups(transforms[i]->model)) break;
      unsigned int materialId = matLib->getMaterialId(transforms[i]->materials[j]);
      //nested if to for to increase renderlist size to needed material index
      if (materialId >= renderList.size()) for (unsigned int i = renderList.size(); i <= materialId; i++) renderList.push_back(std::vector<std::pair<unsigned int, Transform*>>());
      renderList[materialId].push_back(std::pair<unsigned int, Transform*>(j, transforms[i]));
    }
  }
  for (unsigned int i = 0; i < instancedTransforms.size(); i++)
    instancedTransforms[i]->prepareBuffer(camera, projection);

  //shadow map rendering
  Vec3<float> directionalLight(0.5, 2, 0.75);

  //shadow matrix setup
  Matrix<float> lightPerspective;
  Matrix<float> lightMatrix;
  Matrix<float> lightViewMatrix;
  lightPerspective.orthographicView(35, 35, -30, 30);
  lightViewMatrix.lookAt(directionalLight, Vec3<float>(), Vec3<float>(0, 1, 0));
  lightMatrix.translateMatrix(-camObject->getPosition());
  lightMatrix = lightPerspective.multiplyByMatrix(lightViewMatrix.multiplyByMatrix(lightMatrix));

  //draw shadow map
  shadowFbo.bind();
  glViewport(0, 0, 4096, 4096);
  glDisable(GL_CULL_FACE);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(shaderManager->getShader("directionalLight"));
  glUniformMatrix4fv(shaderManager->uniformLocation("directionalLight", "uLightVP"), 1, false, &lightMatrix.matrix[0]);

  bindDefault();
  drawGeometry(renderList, false);

  glUseProgram(shaderManager->getShader("directionalLightInstanced"));  
  glUniformMatrix4fv(shaderManager->uniformLocation("directionalLightInstanced", "uLightVP"), 1, false, &lightMatrix.matrix[0]);

  bindInstance();
  drawInstanced();

  //if post proccesing is enabled bind the correct frame buffer
  if (postProccesStack.size() == 0) glBindFramebuffer(GL_FRAMEBUFFER, 0);
  else storage.bind();

  glEnable(GL_CULL_FACE);
  glViewport(0, 0, width, height);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(shaderManager->getShader("standard"));

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, shadowFbo.getDepth());
  
  glUniformMatrix4fv(shaderManager->uniformLocation("standard", "uLightVP"), 1, false, &lightMatrix.matrix[0]);
  glUniform3f(shaderManager->uniformLocation("standard", "directionalLight"), directionalLight[0], directionalLight[1], directionalLight[2]);

  drawGeometry(renderList, true);
  drawCustom(lightMatrix, directionalLight);
  glUseProgram(shaderManager->getShader("instanced"));
  glUniformMatrix4fv(shaderManager->uniformLocation("instanced", "p"), 1, false, &projection.multiplyByMatrix(camera).matrix[0]);
  glUniformMatrix4fv(shaderManager->uniformLocation("instanced", "uLightVP"), 1, false, &lightMatrix.matrix[0]);
  glUniform3f(shaderManager->uniformLocation("instanced", "directionalLight"), directionalLight[0], directionalLight[1], directionalLight[2]);
  drawInstanced();

  //post procces here
  for (unsigned int j = 0; j < postProccesStack.size(); j++) {
    postProccesStack[j]->draw((j == 0) ? &storage : postProccesStack[j - 1]->getFbo(), ((j + 1) >= postProccesStack.size()));
  }
}

Matrix<float> * RenderModule::getCameraMatrix()
{
  return &camera;
}

void RenderModule::addObject(Object * object)
{
  Transform *  transObj = object->getComponent<Transform>();
  if (transObj && transObj->shouldRender)
  {
    transObj->added();
    transforms.push_back(transObj);

    unsigned int size = geoLib->getTotalGroups(transObj->model);
    unsigned int i = transObj->materials.size();
    std::vector<std::string> materials = geoLib->getGeometry(transObj->model).materials;
  
    for (; i < size; i++)
      transObj->materials.push_back(materials[i]);
  }
  Camera * cam = object->getComponent<Camera>();
  if (cam) camObject = cam;

  CustomShaderTransform * shObj = object->getComponent<CustomShaderTransform>();
  if (shObj) customShaderTransforms.push_back(shObj);

  InstancedTransform * itObj = object->getComponent<InstancedTransform>();
  if (itObj) instancedTransforms.push_back(itObj);
}

//TODO REFRACTOR THIS
void RenderModule::drawCustom(Matrix<float> & lightMatrix, Vec3<float> & directionalLight)
{
  glBindVertexBuffer(0, geoLib->getGeoBufferId(), 0, sizeof(VertexFormat));

  // sorting please dont look at this code its really bad
  //okay this is bad
  std::map<std::string, std::vector<std::vector<std::pair<unsigned int, CustomShaderTransform*>>>> dict;
  for (unsigned int i = 0; i < customShaderTransforms.size(); i++) {
    if (customShaderTransforms[i]->shouldRender) {
      for (unsigned int j = 0; j < customShaderTransforms[i]->materials.size(); j++) 
      {
        unsigned int materialId = matLib->getMaterialId(customShaderTransforms[i]->materials[j]);
        if (materialId >= dict[customShaderTransforms[i]->getShader()].size()) for (unsigned int t = dict[customShaderTransforms[i]->getShader()].size(); t <= materialId; t++) dict[customShaderTransforms[i]->getShader()].push_back(std::vector<std::pair<unsigned int, CustomShaderTransform*>>());
        dict[customShaderTransforms[i]->getShader()][materialId].push_back(std::pair<unsigned int, CustomShaderTransform*>(j, customShaderTransforms[i]));
      }
    }
  }

  //but this is even worse but you know it works
  for (auto const & x : dict) {
    std::string shader = x.first;
    glUseProgram(shaderManager->getShader(shader));
    glUniformMatrix4fv(shaderManager->uniformLocation(shader, "uLightVP"), 1, false, &lightMatrix.matrix[0]);
    glUniform3f(shaderManager->uniformLocation(shader, "directionalLight"), directionalLight[0], directionalLight[1], directionalLight[2]);
    for (unsigned int i = 0; i < x.second.size(); i++) 
    {
      glBindBufferRange(GL_UNIFORM_BUFFER, 0, matLib->matBuffer.getBufferId(), i * sizeof(Material), sizeof(Material));
      unsigned int bufferIndex = -1;
      for (unsigned int j = 0; j < x.second[i].size(); j++)
      {
        x.second[i][j].second->onDraw(shaderManager);
        if (bufferIndex != x.second[i][j].second->bufferIndex)
        {
          bufferIndex = x.second[i][j].second->bufferIndex;
          glBindBufferRange(GL_SHADER_STORAGE_BUFFER, 1, matBufferer.getBufferId(), bufferIndex * sizeof(MatrixBufferObject), sizeof(MatrixBufferObject));
        }
        std::vector<unsigned int> indice = geoLib->getIndice(x.second[i][j].second->model, x.second[i][j].first);
        glDrawElements(GL_TRIANGLES, indice.size(), GL_UNSIGNED_INT, &indice[0]);
        x.second[i][j].second->onDrawExit(shaderManager);
      }

    }
  }
}

void RenderModule::drawInstanced()
{
  for (unsigned int i = 0; i < instancedTransforms.size(); i++)
  {
    glBindVertexBuffer(0, geoLib->getGeoBufferId(), 0, sizeof(VertexFormat));
    glBindVertexBuffer(1, instancedTransforms[i]->getBufferId(), 0, 64);
    for (unsigned int j = 0; j < geoLib->getTotalGroups(instancedTransforms[i]->getModel()); j++) {
      unsigned int materialId = matLib->getMaterialId(instancedTransforms[i]->getMaterial(j));
      glBindBufferRange(GL_UNIFORM_BUFFER, 0, matLib->matBuffer.getBufferId(), materialId * sizeof(Material), sizeof(Material));
      std::vector<unsigned int> indice = geoLib->getIndice(instancedTransforms[i]->getModel(), j);
      glDrawElementsInstanced(GL_TRIANGLES, indice.size(), GL_UNSIGNED_INT, &indice[0], instancedTransforms[0]->getTransformSize());
    }
  }
}

//TODO REFRACTOR THIS
void RenderModule::drawGeometry(std::vector<std::vector<std::pair<unsigned int, Transform*>>> & renderList, bool materials)
{
  glBindVertexBuffer(0, geoLib->getGeoBufferId(), 0, sizeof(VertexFormat));
  for (unsigned int i = 0; i < renderList.size(); i++)
  {
    if (materials) glBindBufferRange(GL_UNIFORM_BUFFER, 0, matLib->matBuffer.getBufferId(), i * sizeof(Material), sizeof(Material));
    unsigned int bufferIndex = -1;
    for (unsigned int j = 0; j < renderList[i].size(); j++)
    {
      if (!renderList[i][j].second->shouldRenderDefault && materials) continue;
      if (bufferIndex != renderList[i][j].second->bufferIndex)
      {
        if (!materials && !renderList[i][j].second->castShadow) break; 
        bufferIndex = renderList[i][j].second->bufferIndex;
        glBindBufferRange(GL_SHADER_STORAGE_BUFFER, 1, matBufferer.getBufferId(), bufferIndex * sizeof(MatrixBufferObject), sizeof(MatrixBufferObject));
      }
      std::vector<unsigned int> indice = geoLib->getIndice(renderList[i][j].second->model, renderList[i][j].first);
      glDrawElements(GL_TRIANGLES, indice.size(), GL_UNSIGNED_INT, &indice[0]);
    }
  }
}

void RenderModule::bindInstance()
{
  glBindVertexArray(instancedVao);
}

void RenderModule::bindDefault()
{
  glBindVertexArray(defaultVao);
}

void RenderModule::setUpInstancedFormat() 
{
  glBindVertexArray(instancedVao);

  glEnableVertexAttribArray(0);
  glVertexAttribFormat(0, 3, GL_FLOAT, false,  0); // position
  glVertexAttribBinding(0, 0); // position -> stream 0

  glEnableVertexAttribArray(1);
  glVertexAttribFormat(1, 3, GL_FLOAT, false, 12); // normal
  glVertexAttribBinding(1, 0); // normal   -> stream 0
  
  glEnableVertexAttribArray(2);
  glVertexAttribFormat(2, 2, GL_FLOAT, false, 24); // texcoord
  glVertexAttribBinding(2, 0); // texcoord -> stream 0

  glEnableVertexAttribArray(3);
  glVertexAttribFormat(3, 4, GL_FLOAT, false, 0);
  glVertexAttribBinding(3, 1);

  glEnableVertexAttribArray(4);
  glVertexAttribFormat(4, 4, GL_FLOAT, false, 16);
  glVertexAttribBinding(4, 1);

  glEnableVertexAttribArray(5);
  glVertexAttribFormat(5, 4, GL_FLOAT, false, 32);
  glVertexAttribBinding(5, 1);

  glEnableVertexAttribArray(6);
  glVertexAttribFormat(6, 4, GL_FLOAT, false, 48);
  glVertexAttribBinding(6, 1);

  glVertexBindingDivisor(1, 1);

}

void RenderModule::setUpFormat()
{
  glBindVertexArray(defaultVao);
  // stream, buffer, offset, stride
  glBindVertexBuffer(0, geoLib->getGeoBufferId(), 0, sizeof(VertexFormat));
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

void RenderModule::updatePerspective(int width, int height, int fov, float near, float far)
{
  projection.perspectiveView(fov, (float)width/height, near, far);
}

void RenderModule::updateOrthoGraphic(int width, int height, float near, float far)
{
  projection.orthographicView((float)width / height * 12, 12, near, far);
}