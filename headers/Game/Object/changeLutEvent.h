#ifndef CHANGELUTEVENT__
#define CHANGELUTEVENT__

#include "System/Graphics/Ui/uiText.h"
#include "System/Engine/EngineObjects/object.h"
#include "Game/Graphics/colorGrade.h"
#include "System/Engine/engine.h"
#include "util/platformUtils.h"

class ChangeLutEvent : public UIText
{
private:
    float updateDelay = 0;
    ColorGrade & color;
    Engine & engine;
    std::vector<std::string> lutNames;
    int currentLut;
    int maxLut;
public:
    ChangeLutEvent(Vec2<float> pos, ColorGrade & colorGrade, Engine & engine, Object * object);
    ~ChangeLutEvent();
    void receiveMessage(const std::string & message, void* data);
    void update();
};

#endif