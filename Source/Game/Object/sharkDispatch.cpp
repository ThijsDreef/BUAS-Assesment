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
    for (unsigned int i = 0; i < timedEvents.size(); i++) {
        timedEvents[i].first -= dt;
        if (timedEvents[i].first < 0) {
					move = -move;

          Vec3<float> target = (*sharkPosition) + (move);

          object->sendMessage(timedEvents[i].second, &target);   
          timedEvents.erase(timedEvents.begin() + i);
        }
    }
}

void SharkDispatch::receiveMessage(const std::string & message, void * data)
{
    if (message == "CIRCLE") {
        timedEvents.push_back(TimedEvent(minDelay + maxDelay * (float)rand() / RAND_MAX, ((float)rand() / RAND_MAX > 0.3) ? "JUMPTO" : "MOVETO"));
        sharkPosition = static_cast<Vec3<float>*>(data);
    }
}