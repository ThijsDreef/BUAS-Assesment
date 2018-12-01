#include "Game/Object/score.h"

Score::Score(Vec2<float> position, Object * object) : UIText("Score: ", position, object)
{

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

void Score::addScore(int addToScore)
{
  scoreDelta += addToScore;
}