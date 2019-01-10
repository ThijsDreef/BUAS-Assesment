#ifndef SINKABLE__
#define SINKABLE__
#include "System/Engine/EngineObjects/object.h"
#include "System/Physics/collisionModule.h"
#include "Util/ease.h"
#include "Math/vec3.h"

class SinkAble : public Component
{
private:
  bool hit = false, loop = false;
  float lowestY;
  float originalY;
  Vec3<float> * targetPos;
  double & dt;
  double timeScale = 0.5;
  double elasticEaseTime = 0;
  double bezierTime = 0;
  float elastic;
  float bezier;
  bool collision = false;
  bool lastCollision = false;
public:
  void update();
  void receiveMessage(const std::string & message, void* data);  
  SinkAble(Vec3<float> * position, float sinkDistance, double & deltaTime, Object * object);
  virtual ~SinkAble();
};

#endif