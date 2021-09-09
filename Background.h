#pragma once

class Background
{
private:
	//Attributes
	sf::Texture texture;
	sf::Sprite sprite;

public:
	//Constructors/Destructors
	Background();

	//Functions
	void update(float deltatime);
	void draw(sf::RenderWindow& window);
};

