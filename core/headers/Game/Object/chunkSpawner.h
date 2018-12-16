#ifndef CHUCNKSPAWNER__
#define CHUCNKSPAWNER__
#include "Game/Object/autoScroller.h"
#include "System/Physics/collisionComponent.h"

class ChunkSpawner : public Component 
{
  AutoScroller * autoScrollerObject;
public:
  ChunkSpawner(AutoScroller * scrollObject, Object * object);
  void update();
  ~ChunkSpawner();
};

#endif