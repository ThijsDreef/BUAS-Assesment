#ifndef PUSHROTATION__
#define PUSHROTATION__
#include "System/Engine/EngineObjects/object.h"
#include "System/Physics/collisionModule.h"
#include "Math/vec3.h"
#include "Math/matrix.h"

class PushOnCollision : public Component
{
private:
    Vec3<float> upVector;
    Vec3<float> * rotation;
    std::string tag;
public:
    PushOnCollision(Vec3<float> up, Vec3<float> * rotation, std::string message, Object * object);
    ~PushOnCollision();
    void receiveMessage(const std::string & message, void* data);
};

#endif