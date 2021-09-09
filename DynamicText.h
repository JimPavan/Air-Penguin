#pragma once

class DynamicText
{
private:
	//Attributes
	sf::Font font;
	sf::Text tapText;

	float opacity;
	float speedOpacity;
	float bound;
	int sideChange;

public:
	//Constructors/Destructors
	DynamicText();

	//Functions
	void update(float deltatime);
	void draw(sf::RenderWindow& window);
};

