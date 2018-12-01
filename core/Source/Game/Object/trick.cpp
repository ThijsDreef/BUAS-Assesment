#include "Game/Object/trick.h"

Trick::Trick(Vec2<float> position, Score * score, Object * object) : UIText("", position, object)
{
  scoreObject = score;
}

Trick::~Trick()
{

}

void Trick::setTrick(std::string trick)
{
  currentTrick = trick;
  enabled = true;
}

void Trick::addToScore(int scoreToAdd)
{
  scoreDelta += scoreToAdd;
}

void Trick::clearTrick()
{
  currentTrick = "";
  scoreObject->addScore(score + scoreDelta);
  score = 0;
  setText(currentTrick);
  enabled = false;
  scoreDelta = 0;
}

void Trick::update()
{
  if (!enabled) return;
  int sd = scoreDelta * 0.15f;
  scoreDelta -= sd;
  score += sd;
  setText(currentTrick + ": " + std::to_string(score));
}