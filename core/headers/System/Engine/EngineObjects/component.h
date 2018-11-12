#ifndef COMPONENT__
#define COMPONENT__
#include <string>
class Object;
class Component
{
protected:
  Object * object;
private:
  bool dead = false;
  int refCounter = 0;
public:
  Component (Object * object);
  virtual ~Component ();
  bool isDead();
  void setDead();
  void added();
  void setRemoved();
  bool isRemoved();
  virtual void receiveMessage(const std::string & message, void* data);
  Object* getObject();
  virtual void start();
  virtual void update();
};
#endif
