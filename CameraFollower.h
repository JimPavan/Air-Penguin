#pragma once
#include "Camera.h"
#include "Player.h"

class CameraFollower : public Camera
{
private:
	//Attributes
	Player& player;

public:
	//Constructors/Destructors
	CameraFollower(float width, float height, Player& player);

	//Functions
	void update(float deltatime);

	//Getters/Setters
	sf::Vector2f getPosition();
};

