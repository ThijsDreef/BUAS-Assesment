#include "Game/Object/autoScroller.h"

AutoScroller::AutoScroller(Vec3<float> spawn, Vec3<float> respawn, Vec3<float> direction, double & deltaTime, Object * object) : Component(object), dt(deltaTime)
{
  spawnLocation = spawn;
  resetLocation = respawn;
  moveDirection = direction;
}

AutoScroller::~AutoScroller()
{

}

unsigned int AutoScroller::getFreeTransformCount()
{
  return freeTransforms.size();
}

Transform* AutoScroller::getFreeTransform()
{
  if (freeTransforms.empty()) return 0;
  Transform * top = freeTransforms.top();
  top->getPos() = spawnLocation;
  freeTransforms.pop();
  return top;
}

void AutoScroller::addTransform(Transform * transform)
{
  transform->shouldRender = true;
  activeTransforms.push_back(transform);
}

void AutoScroller::update()
{
  for (unsigned int i = 0; i < activeTransforms.size(); i++) 
  {
    if (!activeTransforms[i]) activeTransforms.erase(activeTransforms.begin() + i);
    Vec3<float> distance =  activeTransforms[i]->getPos() - resetLocation;
    distance[2] = 0;
    float dist = std::fabs(distance.length());
    if (dist < 2.5) {
      // add to freeTransforms
      freeTransforms.push(activeTransforms[i]);
      // remove here
      activeTransforms.erase(activeTransforms.begin() + i);
    } else {
      activeTransforms[i]->getPos() += moveDirection * dt;
    }
  }
}

