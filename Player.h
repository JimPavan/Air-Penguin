#pragma once
#include "Health.h"
#include "Score.h"

class Player
{
private:
	//Attributes
	sf::Texture texture;
	sf::Sprite sprite;

	const float DECEL_SPEED_IN_AIR = 65;
	const float DIVE_ACCEL = 6000;
	const float GROUND_ACCEL = 450;
	const float MAX_SPEED = 800;
	const float GRAVITY = 750;
	const float MAX_GRAVITY = 1500;
	const float MAX_VSPEED = 1000;

	float velX;
	float velY;
	float speed;
	float rotAngle;
	bool grounded;
	bool accelerating;

	Health health;
	Score score;

public:
	//Constants
	const float AMOUNT_SLIDE_TOUCH = 1.f;
	const float MAX_ROTATION_IN_AIR = 65;
	const float ROTATION_SPEED_IN_AIR = 60;
	const float ROTATION_SPEED_GROUND = 90;
	const float ROTATION_SPEED_ACCELERATION = 200;

	//Constructors/Destructors
	Player();

	//Functions
	void reset();

	void startFalling();
	void stopFalling();

	void instantRotate(float angle);
	void smoothRotate(float targetAngle, float deltatime, float speed);

	void moveByAngle(float angle);
	void updateCurveForce(float angle, float deltatime);
	void updateMovement(float deltatime);

	void update(float deltatime);
	void draw(sf::RenderWindow& window);

	//Getters/Setters
	sf::Sprite getSprite();
	sf::Vector2f getPosition();
	sf::FloatRect getSize();
	void setPosition(sf::Vector2f pos);
	void setAccelerating(bool value);
	bool getAccelerating();
	float getHspeed();
	float getVspeed();
	void setHspeed(float value);
	void setVspeed(float value);
	bool isGrounded();
	void setSpeed(float value);
	float getSpeed();
	Score& getScore();
	Health& getHealth();
};

