#include "Game/Object/PushOnCollision.h"

PushOnCollision::PushOnCollision(Vec3<float> up, Vec3<float> * rotation, std::string tag, Object * object) : Component(object)
{
    upVector = up;
    this->rotation = rotation;
    this->tag = tag;
    object->subscribe("collision", this);
}

PushOnCollision::~PushOnCollision()
{

}

void PushOnCollision::receiveMessage(const std::string & message, void* data)
{
    if (message == "collision") {
        CollisionData * coll = static_cast<CollisionData*>(data);
        if (coll->other->tag == tag) {
            Vec3<float> force = upVector;
            Matrix<float> rotationM;
            rotationM = rotationM.rotation(*rotation);
            force = rotationM.multiplyByVector(force);
            coll->other->getCollisionComponent()->getObject()->sendMessage("push", &force);
        }
    }
}