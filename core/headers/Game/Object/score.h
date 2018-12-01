#ifndef SCORE__
#define SCORE__
#include "System/Graphics/Ui/uiText.h"


class Score : public UIText
{
private:
  int score = 0;
  int scoreDelta = 0;
public:
  Score(Vec2<float> position, Object * object);
  ~Score();
  void update();
  void addScore(int addToScore);
};

#endif
