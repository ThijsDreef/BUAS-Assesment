#include "Game/Object/sinkAble.h"

SinkAble::SinkAble(Vec3<float> * position, float sinkDistance, double & deltaTime, Object * object) : Component(object), dt(deltaTime)
{
  targetPos = position;
  lowestY = (*position)[1] - sinkDistance;
  originalY = (*position)[1];
  object->subscribe("collision", this);
}

SinkAble::~SinkAble()
{

}

void SinkAble::update()
{
  passedTime += (dt * 0.25) * ((hit || lastHit) ? -1 : 1);
  if (hit != lastHit && std::fabs(passedTime) > 0.4) passedTime = 0.4;
  if (passedTime > 0.4) passedTime = 0.4;
  if (passedTime < -0.4) passedTime = -0.4;
  (*targetPos)[1] = Ease::elasticEaseOut(std::fabs(passedTime)) * originalY + (1.0 - Ease::elasticEaseOut(std::fabs(passedTime))) * lowestY;
  lastHit = hit;
  hit = false;
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