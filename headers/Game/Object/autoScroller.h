#ifndef AUTOSCROLLER__
#define AUTOSCROLLER__
#include "System/Engine/EngineObjects/component.h"
#include "System/Engine/EngineObjects/transform.h"
#include "Game/Object/score.h"

#include "Math/vec3.h"
#include <stack>
#include <vector>

class AutoScroller : public Component 
{
private:
  Vec3<float> spawnLocation;
  Vec3<float> resetLocation;
  Vec3<float> moveDirection;
  Score * score;
  double & dt;
  double passedTime = 0;
  float moveScale = 1.0f;
  std::vector<Transform*> activeTransforms;
  std::vector<Vec3<float>*> scrollingVectors;
  std::stack<Transform*> freeTransforms;
public:
  unsigned int getFreeTransformCount();
  Transform* getFreeTransform();
  void addTransform(Transform * transform);
  void addScrollingVector(Vec3<float> * vector);
  void update();
  float & getMoveScale();
  AutoScroller(Vec3<float> spawn, Vec3<float> respawn, Vec3<float> direction, double & deltaTime, Object * object);
  virtual ~AutoScroller();
};

#endif