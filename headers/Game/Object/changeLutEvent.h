#ifndef CHANGELUTEVENT__
#define CHANGELUTEVENT__

#include "System/Engine/EngineObjects/object.h"
#include "Game/Graphics/colorGrade.h"
#include "System/Engine/engine.h"

class ChangeLutEvent : public Component
{
private:
    float updateDelay = 0;
    ColorGrade & color;
    Engine & engine;
    int currentLut;
    int maxLut;
public:
    ChangeLutEvent(ColorGrade & colorGrade, Engine & engine, Object * object);
    ~ChangeLutEvent();
    void receiveMessage(const std::string & message, void* data);
    void update();
};

#endif