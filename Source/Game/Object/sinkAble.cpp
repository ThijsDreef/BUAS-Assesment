#include "Game/Object/sinkAble.h"

SinkAble::SinkAble(Vec3<float> * position, float sinkDistance, double & deltaTime, Object * object) : Component(object), dt(deltaTime)
{
  targetPos = position;
  lowestY = (*position)[1] - sinkDistance;
  originalY = (*position)[1];
  object->subscribe("collision", this);
  bezierTime = 0.5;
  elasticEaseTime = 1;
}

SinkAble::~SinkAble()
{

}

void SinkAble::update()
{
	
  elastic = 1.0 - Ease::cubicEaseOut(std::fabs(elasticEaseTime));
  bezier = Ease::cubicEaseInOut(std::fabs(bezierTime)) * 0.3 + 0.7;
  if (hit) {
    elasticEaseTime -= dt * 1.5;
    if (elasticEaseTime < -1) {
      hit = false;
      
			//elasticEaseTime = 1;
      // bezierTime = 0.5;
    }
    // (*targetPos)[1] = ((elastic * bezier)) * originalY + (1.0 - elastic * ) * lowestY;
  } else {
    bezierTime += dt * ((loop) ? -1 : 1) * timeScale;
    if (bezierTime > 1 || bezierTime < 0) {
      loop = !loop;
      timeScale = 0.3 + (float)rand() / RAND_MAX * 0.2;
    }
  }
  (*targetPos)[1] = (bezier * elastic) * originalY + ((1.0 - elastic) * (1.0 - bezier)) * lowestY;
  lastCollision = collision;
  collision = false;
}

void SinkAble::receiveMessage(const std::string & name, void* data)
{
  if (name == "collision") {
    CollisionData * coll = static_cast<CollisionData*>(data);
    if (coll->firstResolution[1] != 0) {
      collision = true;
      if (!hit && lastCollision != collision) elasticEaseTime = 1;
      if (!hit && lastCollision != collision) hit = true;
    }
  }
}