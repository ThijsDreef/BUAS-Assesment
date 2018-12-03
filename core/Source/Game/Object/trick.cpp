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
  setText(currentTrick + ": " + std::to_string(score + scoreDelta));
  scoreObject->addScore(score + scoreDelta);
  score = 0;
  enabled = false;
  scoreDelta = 0;
}

void Trick::update()
{
  // ugly ass hell needs cleaning
  if (!enabled)
  {
    alpha -= alpha * 0.25;
    return;
  } else 
  {
    alpha += (1 - alpha) * 0.15;
  }
  int sd = scoreDelta * 0.15f;
  scoreDelta -= sd;
  score += sd;
  setText(currentTrick + ": " + std::to_string(score));
}