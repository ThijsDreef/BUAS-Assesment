#include "Game/Object/sinkAble.h"

SinkAble::SinkAble(Vec3<float> * position, float sinkDistance, double & deltaTime, Object * object) : Component(object), dt(deltaTime)
{
  targetPos = position;
  lowestY = (*position)[1] - sinkDistance;
  originalY = (*position)[1];
  object->subscribe("collision", this);
  bezierTime = 0.15;
}

SinkAble::~SinkAble()
{

}

void SinkAble::update()
{
  elastic = Ease::elasticEaseOut(std::fabs(elasticEaseTime));
  bezier = Ease::cubicEaseInOut(std::fabs(bezierTime));
  if (hit) {
    elasticEaseTime -= dt * 0.25;
    if (elasticEaseTime < -0.15) {
      hit = false;
      loop = false;
    }
    (*targetPos)[1] = (1.0 - elastic) * originalY + (elastic) * lowestY;
  } else {
    bezierTime += dt * 0.25 * ((loop) ? -1 : 1) * timeScale;
    if (bezierTime > 0.18 || bezierTime < 0.13) {
      loop = !loop;
      timeScale = 0.5f + (float)rand() / RAND_MAX * 0.1;
    }
    (*targetPos)[1] = bezier * originalY + (1.0 - bezier) * lowestY;
  }
  lastCollision = collision;
  collision = false;
}

void SinkAble::receiveMessage(const std::string & name, void* data)
{
  if (name == "collision") {
    CollisionData * coll = static_cast<CollisionData*>(data);
    if (coll->firstResolution[1] != 0) {
      collision = true;
      if (!hit && lastCollision != collision) elastic = 0.15;
      if (!hit && lastCollision != collision) hit = true;
    }
  }
}