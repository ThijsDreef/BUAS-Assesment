#ifndef EVENTONKEY__
#define EVENTONKEY__

#include "System/Engine/EngineObjects/object.h"
#include "System/Input/input.h"
typedef std::pair<int, std::string> KeyEvent;

class EventOnKey : public Component
{
private:
  std::vector<KeyEvent> keyEvents;
  Input * input;
public:
  EventOnKey(std::vector<KeyEvent> events, Input * input, Object * object);
  ~EventOnKey();
  void update();
};

#endif