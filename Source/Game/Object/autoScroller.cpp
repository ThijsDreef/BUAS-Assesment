#include "Game/Object/autoScroller.h"

AutoScroller::AutoScroller(Vec3<float> spawn, Vec3<float> respawn, Vec3<float> direction, double & deltaTime, Object * object) : Component(object), dt(deltaTime)
{
  spawnLocation = spawn;
  resetLocation = respawn;
  moveDirection = direction;
  score = object->getComponent<Score>();
}

AutoScroller::~AutoScroller()
{

}

unsigned int AutoScroller::getFreeTransformCount()
{
  return freeTransforms.size();
}

float & AutoScroller::getMoveScale()
{
  return moveScale;
}

Transform* AutoScroller::getFreeTransform()
{
  if (freeTransforms.empty()) return 0;
  Transform * top = freeTransforms.top();
  top->getPos() = (top->getPos() * (Vec3<float>(1, 1, 1) - moveDirection.normalize().abs())) + (spawnLocation * moveDirection.normalize().abs());
  freeTransforms.pop();
  return top;
}

void AutoScroller::addTransform(Transform * transform)
{
  transform->shouldRender = true;
  activeTransforms.push_back(transform);
}

void AutoScroller::addScrollingVector(Vec3<float> * vector)
{
  scrollingVectors.push_back(vector);
}

void AutoScroller::update()
{
  passedTime += dt;
  if (passedTime > 10) {
    passedTime = 0;
    moveScale *= 1.1;
  }
  score->addScore(std::fabs(moveDirection.length()) * dt * moveScale);
  for (unsigned int i = 0; i < scrollingVectors.size(); i++)
  {
    if (!scrollingVectors[i]) scrollingVectors.erase(scrollingVectors.begin() + i);
    *scrollingVectors[i] += moveDirection * dt * moveScale;
    Vec3<float> distance = (*scrollingVectors[i]) - resetLocation;
    
    if (distance.length() < 2.5)
    {
      (*scrollingVectors[i])[0] = spawnLocation[0];
    }
  }
  for (unsigned int i = 0; i < activeTransforms.size(); i++) 
  {
    if (!activeTransforms[i]) activeTransforms.erase(activeTransforms.begin() + i);
    Vec3<float> distance = activeTransforms[i]->getPos() - resetLocation;
    distance[2] = 0;
    distance[1] = 0;
    float dist = std::fabs(distance.length());
		//so we dont replace anything that doesnt want to be rendered "like inactive particles"
    if (dist < 2.5 && activeTransforms[i]->shouldRender) {
      // add to freeTransforms
      activeTransforms[i]->shouldRender = false;
      freeTransforms.push(activeTransforms[i]);
      // remove here
      activeTransforms.erase(activeTransforms.begin() + i);
    } else {
      activeTransforms[i]->getPos() += moveDirection * dt * moveScale;
    }
  }
}

