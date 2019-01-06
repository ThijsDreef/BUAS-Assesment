#include "Game/Object/chunkSpawner.h"

ChunkSpawner::ChunkSpawner(AutoScroller * scrollObject, Object * object) : Component(object)
{
  autoScrollerObject = scrollObject;
}

ChunkSpawner::~ChunkSpawner()
{

}

void ChunkSpawner::update()
{
  while (autoScrollerObject->getFreeTransformCount() != 0) {
    Transform * transform = autoScrollerObject->getFreeTransform();
		transform->getObject()->sendMessage("Respawn", 0);
    transform->getPos()[2] = ((float)rand() / (float)RAND_MAX) * 25.0f - 17.5f;
    CollisionComponent * coll = transform->getObject()->getComponent<CollisionComponent>();
    if (coll) coll->getCollider()->setScale(transform->getScale());
    autoScrollerObject->addTransform(transform);
  }
}