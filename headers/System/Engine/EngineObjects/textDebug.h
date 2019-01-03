#ifndef TEXTDEBUG__
#define TEXTDEBUG__

#include "System/Graphics/Ui/uiText.h"

template<class DATA>
class TextDebug : public UIText
{
private:
  DATA * dataPointer;
  std::string baseText;
public:
  TextDebug(std::string baseText, Vec2<float> position, DATA * pointer, Object * object) : UIText(baseText, position, object)
  {
    dataPointer = pointer;
    this->baseText = baseText;
    scale = 0.5;
  };
  virtual ~TextDebug() 
  {

  };
  void update()
  {
    setText(baseText + std::to_string(*dataPointer));
  };
  void setBaseText(std::string base)
  {
    baseText = base;
  };
  void setPointer(DATA * pointer)
  {
    dataPointer = pointer;
  };
};

#endif