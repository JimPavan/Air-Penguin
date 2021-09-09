#pragma once
#include "DynamicText.h"

class MenuState
{
private:
	//Attributes
	DynamicText dynamicText;
	bool click;

public:
	//Constructors/Destructors
	MenuState();

	//Functions
	void checkTap();
	virtual void update(float deltatime);
	virtual void draw(sf::RenderWindow& window);

	//Getters/Setters
	bool isClick();
};

