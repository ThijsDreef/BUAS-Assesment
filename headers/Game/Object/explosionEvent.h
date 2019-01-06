#ifndef EXPLOSIONEVENT__
#define EXPLOSIONEVENT__

#include "System/Engine/EngineObjects/particleSystem.h"

class ExplosionEvent : public ParticleSystem 
{
private:
	double & dt;
public: 
  ExplosionEvent(Object * subscribeObject, double & deltaTime, Object * object);
  ~ExplosionEvent();
  virtual void update();
  void receiveMessage(const std::string & message, void * data);
};
#endif