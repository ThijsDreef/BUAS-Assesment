#ifndef COINONCOLLISION__
#define COINONCOLLISION__

#include "System/Engine/EngineObjects/object.h"
#include "System/Engine/EngineObjects/transform.h"
#include "System/Physics/collisionModule.h"


class CoinOnCollision : public Component
{
private:
  double & dt;
  bool hit = false;
  Transform * transform;
  float toAddScore = 50.0f;
public:
  CoinOnCollision(double & deltaTime, Object * object);
  virtual ~CoinOnCollision();
  void receiveMessage(const std::string & message, void * data);
};

#endif