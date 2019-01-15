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
  float * moveScale = 0;
  float jumpHeight = 30;
  float swimHeight = -10;
  float jumpTime = 1/3.0f;
  Vec3<float> originalFromJump;
  Vec3<float> * chaseTarget;
  double passedTime = 0;
  double & dt;
  Vec3<float> getLookAtRotation(Vec3<float> from, Vec3<float> to);
  float interpolateEulerAngle(int from, int to, float speed);
  void lookAt(Vec3<float> to, float speed);
  void circle();
  void moveTo();
  void jumpTo();
  void chase();
public:
  Vec3<float> & getOriginalFromJump();
  Vec3<float> & getTarget();
  SharkStateMachine(double & deltaTime, Object * object);
  ~SharkStateMachine();
  void setMoveScale(float * scale);
  void setChase(Vec3<float> * toChase);
  void jumpTo(Vec3<float> target);
  void setJumpTime(float time);
  void update();
  void receiveMessage(const std::string & message, void* data);
};

#endif