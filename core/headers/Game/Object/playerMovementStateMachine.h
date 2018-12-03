#ifndef PLAYERMOVEMENTSTATEMACHINE__
#define PLAYERMOVEMENTSTATEMACHINE__

#include "System/Engine/EngineObjects/object.h"
#include "System/Physics/Colliders/collider.h"
#include "Game/Object/rotateToMouse.h"
#include "Game/Object/trick.h"
#include "Math/Vec3.h"

enum PlayerMoveState {
    DEFAULT,
    AIRTIME,
    PIROUTE,
    SPEEDING
};

class PlayerMoveStateMachine : public Component
{
private:
    double passedTime = 0.0;
    bool grounded = false;
    Input * input;
    Vec3<float> * posPointer;
    Vec3<float> * rotPointer;
    Vec3<float> force;
    Trick * trickObject;
    PlayerMoveState currentState = DEFAULT;
    void defaultState();
    void airTimeState();
    void pirouteState();
    void speedingState();
    RotateToMouse * rotationComponent;
    double & dt;
public:
    PlayerMoveStateMachine(Vec3<float> * positionTarget, Vec3<float> * rotationTarget, Input * input, Trick * trickObject, double & deltaTime, Object * object);
    virtual ~PlayerMoveStateMachine();
    void update();
    void receiveMessage(const std::string & message, void* data);
};

#endif