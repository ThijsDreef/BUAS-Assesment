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
    float random = (float)rand() / RAND_MAX;
    Vec3<float> scale = Vec3<float>(random * 10 + 4, 5, random * 10 + 4);
    transform->getScale() = scale;
    transform->getPos()[2] += ((float)rand() / (float)RAND_MAX) * 30.0f - 15.0f;
    transform->getObject()->getComponent<CollisionComponent>()->getCollider()->setScale(scale);
    autoScrollerObject->addTransform(transform);
  }
}