#pragma once

class Gauge
{
private:
	//Attributes
	float x;
	float y;
	float width;
	float height;

	sf::RectangleShape backRect;
	sf::RectangleShape frontRect;

	sf::Color backColor;
	sf::Color frontColor;

public:
	//Constructors/Destructors
	Gauge();

	//Functions
	void update(float ratio);
	void draw(sf::RenderWindow& window);
};

