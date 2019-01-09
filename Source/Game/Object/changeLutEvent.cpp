#include "Game/Object/changeLutEvent.h"

ChangeLutEvent::ChangeLutEvent(ColorGrade & colorGrade, Engine & engineObject, Object * object) : Component(object), color(colorGrade), engine(engineObject)
{
    currentLut = engine.options.getOptionI("currentLut");
    maxLut = engine.options.getOptionI("lutNumber");
    object->subscribe("incrementLut", this);
    object->subscribe("decrementLut", this);
}

ChangeLutEvent::~ChangeLutEvent()
{

}

void ChangeLutEvent::update()
{
    updateDelay -= engine.deltaTime;
}

void ChangeLutEvent::receiveMessage(const std::string & message, void * data)
{
    if (message == "incrementLut" && updateDelay < 0) {
        updateDelay = 0.3;
        currentLut ++;
        currentLut %= maxLut;
        engine.options.setOption(OptionData("currentLut", "lut" + std::to_string(currentLut)));
        color.setTexture(engine.getMatLib()->getTexture("lut" + std::to_string(currentLut)));
    } else if (message == "decrementLut" && updateDelay < 0) {
        currentLut --;
        updateDelay = 0.3;
        currentLut = (currentLut >= 0) ? currentLut : maxLut - 1;
        engine.options.setOption(OptionData("currentLut", "lut" + std::to_string(currentLut)));
        color.setTexture(engine.getMatLib()->getTexture("lut" + std::to_string(currentLut)));
    }
}