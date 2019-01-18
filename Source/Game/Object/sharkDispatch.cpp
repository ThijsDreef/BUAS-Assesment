#include "Game/Object/sharkDispatch.h"
#include <iostream>

SharkDispatch::SharkDispatch( Vec3<float> max, Vec3<float> min, double & deltaTime, Object * object) : Component(object), dt(deltaTime)
{
    maxMove = max;
    minMove = min;
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
            Vec3 <float> move = minMove;
            // move[0] = (back) ? move[0] : -move[0];
            move[2] = (back) ? move[2] : -move[2];

            Vec3<float> target = (*sharkPosition) + (move);

            back = !back;
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