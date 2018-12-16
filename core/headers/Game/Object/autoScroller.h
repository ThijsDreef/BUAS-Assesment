#ifndef AUTOSCROLLER__
#define AUTOSCROLLER__
#include "System/Engine/EngineObjects/component.h"
#include "System/Engine/EngineObjects/transform.h"
#include "Math/vec3.h"
#include <stack>
#include <vector>

class AutoScroller : public Component 
{
private:
  Vec3<float> spawnLocation;
  Vec3<float> resetLocation;
  Vec3<float> moveDirection;
  double & dt;
  std::vector<Transform*> activeTransforms;
  std::stack<Transform*> freeTransforms;
public:
  unsigned int getFreeTransformCount();
  Transform* getFreeTransform();
  void addTransform(Transform * transform);
  void update();
  AutoScroller(Vec3<float> spawn, Vec3<float> respawn, Vec3<float> direction, double & deltaTime, Object * object);
  ~AutoScroller();
};

#endif