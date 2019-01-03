#ifndef COLLIDER__
#define COLLIDER__
#include "Math/vec3.h"
#include <string>

class CollisionComponent;
class Collider {
protected:
  Vec3<float> p;
  Vec3<float> scale;
public:
  bool isStatic = false;
  bool isMoveAble = true;
  bool isTrigger = false;
  std::string tag = "none";
  Collider ();
  virtual ~Collider ();
  virtual bool intersectB(Collider * other);
  virtual Vec3<float> intersectA(Collider * other);
  void setPos(Vec3<float> & pos);
  std::string & getResolver();
  Vec3<float> & getPos();
  void syncPos(Vec3<float> * pos);
  void setScale(Vec3<float> s);
  void setCollisionComponent(CollisionComponent * component);
  CollisionComponent * getCollisionComponent();
private:
  CollisionComponent * collComponent = nullptr;
  Vec3<float> * posPointer = nullptr;
};

#endif
