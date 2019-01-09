#include "Game/Object/changeLutEvent.h"

ChangeLutEvent::ChangeLutEvent(Vec2<float> pos, ColorGrade & colorGrade, Engine & engineObject, Object * object) : UIText("", pos, object), color(colorGrade), engine(engineObject)
{
    scale = 1;
    alpha = 1;
    currentLut = engine.options.getOptionI("currentLut");
    std::cout << currentLut << "\n";
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
    setText(lutNames[currentLut]);
    color.setTexture(engine.getMatLib()->getTexture("lut" + std::to_string(currentLut)));
    shouldCenter = true;

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
        setText(lutNames[currentLut]);
    } else if (message == "decrementLut" && updateDelay < 0) {
        currentLut --;
        updateDelay = 0.3;
        currentLut = (currentLut >= 0) ? currentLut : maxLut - 1;
        engine.options.setOption(OptionData("currentLut", "lut" + std::to_string(currentLut)));
        color.setTexture(engine.getMatLib()->getTexture("lut" + std::to_string(currentLut)));
        setText(lutNames[currentLut]);
    }
}