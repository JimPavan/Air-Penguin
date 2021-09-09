#pragma once

class Score
{
private:
	//Constants
	const float PIXELS_TO_METERS = 100;

	//Attributes
	float score;

	float offsetX;

public:
	//Constructors/Destructors
	Score();

	//Functions
	void setStartOffset(float offsetx);
	void update(float posx);

	//Getters/Setters
	float getScore();
};

