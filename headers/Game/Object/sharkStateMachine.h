#ifndef SHARKSTATEMACHINE__
#define SHARKSTATEMACHINE__
#include "System/Engine/EngineObjects/object.h"
#include "System/Engine/EngineObjects/transform.h"
#include "Util/ease.h"

// dutch humor btw
// also know as AHAAi
enum SharkState {CIRCLE, MOVETO, JUMPTO};

class SharkStateMachine : public Component
{
private:
  Transform * sharkTransform;
  SharkState state;
  Vec3<float> target = Vec3<float>(0, -10, 0);
  double passedTime = 0;
  double & dt;
  void circle();
  void moveTo();
  void jumpTo();
public:
  SharkStateMachine(double & deltaTime, Object * object);
  ~SharkStateMachine();
  void update();
  void receiveMessage(const std::string & message, void* data);
};

#endif