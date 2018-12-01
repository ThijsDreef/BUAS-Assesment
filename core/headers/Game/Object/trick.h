#ifndef TRICK__
#define TRICK__
#include "System/Graphics/Ui/uiText.h"


class Trick : public UIText
{
private:
  std::string currentTrick;
  int score;
  int scoreDelta;
public:
  Trick(Object * object);
  ~Trick();
  void setTrick(std::string trick);
  void addToScore(int scoreToAdd);
  void clearTrick();
  void update();


};

#endif