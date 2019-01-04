#include "Game/Object/sinkAble.h"

SinkAble::SinkAble(Vec3<float> * position, float sinkDistance, double & deltaTime, Object * object) : Component(object), dt(deltaTime)
{
  targetPos = position;
  lowestY = (*position)[1] - sinkDistance;
  originalY = (*position)[1];
  object->subscribe("collision", this);
  passedTime = 0.35;
}

SinkAble::~SinkAble()
{

}

void SinkAble::update()
{
  if (hit) {
    passedTime -= dt * 0.25;
    if (passedTime < -0.4) {
      hit = false;
      loop = false;
      passedTime = 0.4;
    }
  } else {
    passedTime += dt * 0.25 * ((loop) ? -1 : 1) * timeScale;
    if (passedTime > 0.4 || passedTime < 0.3) {
      loop = !loop;
      timeScale = fmax((float)rand() / RAND_MAX, 0.45);
    }
  }
  (*targetPos)[1] = Ease::elasticEaseOut(std::fabs(passedTime)) * originalY + (1.0 - Ease::elasticEaseOut(std::fabs(passedTime))) * lowestY;
}

void SinkAble::receiveMessage(const std::string & name, void* data)
{
  if (name == "collision") {
    CollisionData * coll = static_cast<CollisionData*>(data);
    if (coll->firstResolution[1] != 0) {
      hit = true;
    }
  }
}