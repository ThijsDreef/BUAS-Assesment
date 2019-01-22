#include "Game/Object/sharkDispatch.h"
#include <iostream>

SharkDispatch::SharkDispatch(Vec3<float> moveVector, double & deltaTime, Object * object) : Component(object), dt(deltaTime)
{
    move = moveVector;
    object->subscribe("CIRCLE", this);
}

SharkDispatch::~SharkDispatch()
{

}

void SharkDispatch::update()
{
    event.first -= dt;
    if (event.first < 0 && !fired) {
        move = -move;   

        Vec3<float> target = (*sharkPosition) + (move);

        object->sendMessage(event.second, &target);   
        fired = true;
    }
}

void SharkDispatch::receiveMessage(const std::string & message, void * data)
{
    if (message == "CIRCLE") {
        event = TimedEvent(minDelay + maxDelay * (float)rand() / RAND_MAX, ((float)rand() / RAND_MAX > 0.3) ? "JUMPTO" : "MOVETO");
        sharkPosition = static_cast<Vec3<float>*>(data);
        fired = false;
    }
}