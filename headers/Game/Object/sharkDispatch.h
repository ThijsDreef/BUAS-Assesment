#ifndef SHARKDISPATCH__
#define SHARKDISPATCH__
#include "System/Engine/EngineObjects/object.h"
#include "Math/vec3.h"

typedef std::pair<double, std::string> TimedEvent;

class SharkDispatch : public Component
{
private:
  double & dt;
  float maxDelay = 2;
  float minDelay = 1;
  Vec3<float> move;
  Vec3<float> * sharkPosition;
  bool fired = true;
  TimedEvent event;
public:
  SharkDispatch(Vec3<float> min, double & deltaTime, Object * object);
  ~SharkDispatch();
  void update();
  void receiveMessage(const std::string & message, void * data);
};


#endif