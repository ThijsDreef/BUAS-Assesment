#include "System/Engine/scene.h"

Scene::Scene(std::vector<Object*> startObjects, std::vector<std::vector<Module*>> startModules)
{
  objects = startObjects;
  modules = startModules;
  for (unsigned int j = 0; j < objects.size(); j++)
    for (unsigned int i = 0; i < modules.size(); i++)
      for (unsigned int k = 0; k < modules[i].size(); k++)
        modules[i][k]->addObject(objects[j]);
}

Scene::~Scene()
{
  for (unsigned int i = 0; i < modules.size(); i++)
    for (unsigned int j = 0; j < modules[i].size(); j++)
      delete modules[i][j];
  for (unsigned int i = 0; i < objects.size(); i++)
    delete objects[i];
}

void Scene::update()
{
  for (unsigned int i = 0; i < objects.size(); i++)
    if (!objects[i]->empty())
      objects[i]->updateComponents();
  for (unsigned int i = 0; i < modules.size(); i++)
    for (unsigned int j = 0; j < modules[i].size(); j++)
      modules[i][j]->update();
}

void Scene::addObject(Object * object)
{
  for (unsigned int i = 0; i < modules.size(); i++)
    for (unsigned int j = 0; j < modules[i].size(); j++)
      modules[i][j]->addObject(object);
  objects.push_back(object);
}

void Scene::addModule(Module * module)
{
  for (unsigned int i = 0; i < objects.size(); i++)
    module->addObject(objects[i]);
  modules[0].push_back(module);
}

void Scene::addModule(Module * module, unsigned int index)
{
  while (index > modules.size())
    modules.push_back(std::vector<Module*>());
  for (unsigned int i = 0; i < objects.size(); i++)
    module->addObject(objects[i]);
  modules[index].push_back(module);
}
