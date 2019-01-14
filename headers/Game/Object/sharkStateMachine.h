#ifndef SHARKSTATEMACHINE__
#define SHARKSTATEMACHINE__
#include "System/Engine/EngineObjects/object.h"
#include "System/Engine/EngineObjects/transform.h"
#include "Util/ease.h"

// dutch humor btw
// also know as AHAAi
enum SharkState {CIRCLE, MOVETO, JUMPTO, CHASE};

class SharkStateMachine : public Component
{
private:
  Transform * sharkTransform;
  SharkState state;
  Vec3<float> target = Vec3<float>(0, -10, 0);
  Vec3<float> * chaseTarget;
  double passedTime = 0;
  double & dt;
  Vec3<float> getLookAtRotation(Vec3<float> from, Vec3<float> to);
  void circle();
  void moveTo();
  void jumpTo();
  void chase();
public:
  SharkStateMachine(double & deltaTime, Object * object);
  ~SharkStateMachine();
  void setChase(Vec3<float> * toChase);
  void update();
  void receiveMessage(const std::string & message, void* data);
};

#endif