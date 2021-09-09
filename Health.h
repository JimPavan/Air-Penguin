#pragma once

class Health
{
private:
	//Constants
	const float X_HEALTH_THRESHOLD = 400;
	const float Y_HEALTH_THRESHOLD = 200;
	const float LIFE_GAIN = 20;
	const float MAX_HEALTH = 100;

	//Attributes
	float health;

public:
	//Constructors/Destructors
	Health();

	//Functions
	void update(float deltatime, float posx, float posy);

	//Getters/Setters
	float getHealth();
	float getHealthRatio();
	void setHealth(float ratio);
};

