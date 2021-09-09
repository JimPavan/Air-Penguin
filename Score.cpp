#include "stdafx.h"
#include "Score.h"

Score::Score()
{

}

void Score::setStartOffset(float offsetx)
{
	//Prevent score greater than 0 when starting new game

	score = 0;
	offsetX = offsetx;
}

void Score::update(float posx)
{
	score = (posx - offsetX) / PIXELS_TO_METERS;
}

float Score::getScore()
{
	return score;
}
