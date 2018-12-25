#ifndef SINKABLE__
#define SINKABLE__
#include "System/Engine/EngineObjects/object.h"
#include "Math/vec3.h"

class SinkAble : public Component
{
private:
  bool hit, lastHit;
  float lowestY;
  float originalY;
  Vec3<float> * targetPos;
  double & dt;
  double passedTime = 0;
public:
  void update();
  void receiveMessage(const std::string & message, void* data);  
  SinkAble(Vec3<float> * position, float sinkDistance, double & deltaTime, Object * object);
  ~SinkAble();
};

#endif