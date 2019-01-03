#ifndef OBJECT__
#define OBJECT__
#include <vector>
#include <string>
#include <map>
#include "System/Engine/EngineObjects/component.h"

class Object
{
private:
  std::vector<Component*> components;
  std::map<std::string, std::vector<Component*>> event;
public:
  Object (std::vector<Component*> comp);
  void updateComponents();
  bool empty();
  void addComponent(Component * comp);
  void sendMessage(const std::string & message, void* data);
  void subscribe(const std::string & message, Component * c);
  virtual ~Object ();
  template<class T>
  void removeComponents()
  {
    for (unsigned int i = 0; i < components.size(); i ++)
    {
      if (dynamic_cast<T*>(components[i]))
      {
          delete components[i];
          components.erase(components.begin() + i);
          i --;
      }
    }
  }
  template<class T>
  T * getComponent()
  {
    for (unsigned int i = 0; i < components.size(); i++)
    {
      T * temp = dynamic_cast<T*>(components[i]);
      if (temp != 0)
        return temp;
    }
    return 0;
  }
};
#endif
