#include "Game/Object/score.h"

Score::Score(Vec2<float> position, Object * object) : UIText("Score: ", position, object)
{
  alpha = 0.5;
}

Score::~Score()
{

}

void Score::update()
{
  int sd = scoreDelta * 0.15f;
  scoreDelta -= sd;
  score += sd;
  setText("Score: " + std::to_string(score));
}

void Score::addScore(float addToScore)
{
  scoreDelta += addToScore;
}