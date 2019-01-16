#ifndef SHARKDISPATCH__
#define SHARKDISPATCH__
#include "System/Engine/EngineObjects/object.h"

class SharkDispatch : public Component
{
public:
  SharkDispatch(Object * object);
  ~SharkDispatch();
  void update();
  void receiveMessage(const std::string & message, void * data);
};


#endif