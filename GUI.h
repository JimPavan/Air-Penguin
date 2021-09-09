#pragma once
#include "Score.h"
#include "Health.h"
#include "Gauge.h"

class GUI
{
private:
	//Attributes
	sf::Font font;
	sf::Text airText;
	sf::Text scoreText;

	Gauge gauge;

	float fontSize;
	float yPos;
	float airTextX;
	float scoreTextX;

public:
	//Constructors/Destructors
	GUI();

	//Functions
	void update(Score& score, Health& health);
	void draw(sf::RenderWindow& window);
};