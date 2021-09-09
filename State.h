#pragma once
#include "Camera.h"

class State
{
private:
	//Attributes
	Camera camera;

public:
	//Constructors/Destructors
	State();

	//Functions
	virtual void update(float deltatime);
	virtual void draw(sf::RenderWindow& window);
};

