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
  if (autoScrollerObject->getFreeTransformCount() != 0) {
    Transform * transform = autoScrollerObject->getFreeTransform();
    float randomX = (float)rand() / RAND_MAX;
    float randomY = (float)rand() / RAND_MAX;

    Vec3<float> scale = Vec3<float>(randomX * 5 + 4, 5, randomY * 5 + 4);
    transform->getScale() = scale;
    transform->getPos()[2] += ((float)rand() / (float)RAND_MAX) * 25.0f - 17.5f;
    transform->getObject()->getComponent<CollisionComponent>()->getCollider()->setScale(scale);
    autoScrollerObject->addTransform(transform);
  }
}