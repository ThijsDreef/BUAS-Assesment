#ifndef SCORE__
#define SCORE__
#include "System/Graphics/Ui/uiText.h"
#include "System/Engine/EngineObjects/object.h"


class Score : public UIText
{
private:
  int score = 0;
  float scoreDelta = 0;
public:
  Score(Vec2<float> position, Object * object);
  virtual ~Score();
  void update();
  void addScore(float addToScore);
  void receiveMessage(const std::string & message, void* data);
};

#endif
