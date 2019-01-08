#include "Game/Object/score.h"

Score::Score(Vec2<float> position, Object * object) : UIText("Score: ", position, object)
{
  alpha = 0.5;
  object->subscribe("addScore", this);
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

void Score::receiveMessage(const std::string & message, void* data)
{
	if (message == "addScore") {
		addScore(*static_cast<float*>(data));
	}
}