#ifndef MODULE__
#define MODULE__
class Object;
class Module
{
public:
  Module ();
  virtual ~Module ();
  virtual void update();
  virtual void addObject(Object * obj);
};
#endif
