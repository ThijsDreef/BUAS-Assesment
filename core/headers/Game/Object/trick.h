#ifndef TRICK__
#define TRICK__
#include "System/Graphics/Ui/uiText.h"
#include "Game/Object/score.h"


class Trick : public UIText
{
private:
  std::string currentTrick;
  int score = 0;
  int scoreDelta = 0;
  Score * scoreObject;
  bool enabled = false;
public:
  Trick(Vec2<float> position, Score * score, Object * object);
  ~Trick();
  void setTrick(std::string trick);
  void addToScore(int scoreToAdd);
  void clearTrick();
  void update();


};

#endif