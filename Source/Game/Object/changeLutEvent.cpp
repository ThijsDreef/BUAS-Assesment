#include "Game/Object/changeLutEvent.h"

ChangeLutEvent::ChangeLutEvent(Vec2<float> pos, ColorGrade & colorGrade, Engine & engineObject, Object * object) : UIText("color grade: ", pos, object), color(colorGrade), engine(engineObject)
{
    scale = 0.5;
    alpha = 0.5;
    currentLut = engine.options.getOptionI("currentLut");
    maxLut = engine.options.getOptionI("lutNumber");
    object->subscribe("incrementLut", this);
    object->subscribe("decrementLut", this);
    std::vector<std::string> files;
    PlatformUtils::readDirectory("shaders/postProccesing/luts", files);
    for (unsigned int i = 0; i < files.size(); i++) {
        if (files[i].length() > 4 && files[i].substr(files[i].length() - 4, files[i].length()) == ".png") {
            lutNames.push_back(files[i].substr(0, files[i].length() - 4));
        }
    }
    setText("color grade: " + lutNames[currentLut]);
    color.setTexture(engine.getMatLib()->getTexture("lut" + std::to_string(currentLut)));
    

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
        engine.options.setOption(OptionData("currentLut", std::to_string(currentLut)));
        color.setTexture(engine.getMatLib()->getTexture("lut" + std::to_string(currentLut)));
        setText("color grade: " + lutNames[currentLut]);
    } else if (message == "decrementLut" && updateDelay < 0) {
        currentLut --;
        updateDelay = 0.3;
        currentLut = (currentLut >= 0) ? currentLut : maxLut - 1;
        engine.options.setOption(OptionData("currentLut", std::to_string(currentLut)));
        color.setTexture(engine.getMatLib()->getTexture("lut" + std::to_string(currentLut)));
        setText("color grade: " + lutNames[currentLut]);
    }
}