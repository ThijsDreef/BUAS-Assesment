#ifndef COINONCOLLISION__
#define COINONCOLLISION__

#include "System/Engine/EngineObjects/object.h"
#include "System/Engine/EngineObjects/transform.h"


class CoinOnCollision : public Component
{
private:
  double & dt;
  bool hit = false;
  Transform * transform;
public:
  CoinOnCollision(double & deltaTime, Object * object);
  virtual ~CoinOnCollision();
  void receiveMessage(const std::string & message, void * data);
};

#endif