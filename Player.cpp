#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	texture = sf::Texture();
	texture.loadFromFile("penguinSprite.png");

	sprite = sf::Sprite(texture);
	sprite.setPosition(sf::Vector2f(10, 0));
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

	velX = 0;
	velY = 0;
	speed = 0;
	rotAngle = 0;
	grounded = false;
	accelerating = false;
}

void Player::reset()
{
	sprite.setPosition(sf::Vector2f(10, 0));

	velX = 0;
	velY = 0;
	speed = 0;
	rotAngle = 0;
	grounded = false;
	accelerating = false;
}

void Player::update(float deltatime)
{
	//Update physics and logic
	updateMovement(deltatime);

	if (accelerating)
		smoothRotate(MAX_ROTATION_IN_AIR, deltatime, ROTATION_SPEED_ACCELERATION);

	sprite.move(sf::Vector2f(velX * deltatime, velY * deltatime));
	sprite.setRotation(rotAngle);

	//Update score and health
	score.update(sprite.getPosition().x);
	health.update(deltatime, sprite.getPosition().x, sprite.getPosition().y);
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Player::instantRotate(float angle)
{
	rotAngle = angle;
}

void Player::stopFalling()
{
	grounded = true;
}

void Player::startFalling()
{
	grounded = false;
}

sf::Sprite Player::getSprite()
{
	return this->sprite;
}

void Player::smoothRotate(float targetAngle, float deltatime, float speed)
{
	rotAngle += speed * deltatime;

	if (rotAngle > targetAngle)
		rotAngle = targetAngle;
}

void Player::setPosition(sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::updateMovement(float deltatime)
{
	if (accelerating)
	{
		// Acceleration dive down 
		// and increase speed for when it touches the ground
		velY += DIVE_ACCEL * deltatime;
		if (!grounded)
			speed += DIVE_ACCEL * deltatime;
		else
			speed += GROUND_ACCEL * deltatime;

		// Cap max speed
		if (speed > MAX_SPEED)
			speed = MAX_SPEED;

		// Cap max diving down velocity
		if (velY > MAX_GRAVITY)
			velY = MAX_GRAVITY;
	}

	if (!grounded)
	{
		// Update natural physics when in air
		velY += GRAVITY * deltatime;
		speed -= DECEL_SPEED_IN_AIR * deltatime;
		speed = std::max(0.f, speed);
	}

	if (velY < -MAX_VSPEED)
		velY = -MAX_VSPEED;
}

void Player::moveByAngle(float angle)
{
	// Move by angle the player
	velX = speed * cos(angle);
	velY = speed * sin(angle);
}

void Player::setAccelerating(bool value)
{
	accelerating = value;
}

sf::Vector2f Player::getPosition()
{
	return sprite.getPosition();
}

sf::FloatRect Player::getSize()
{
	return sprite.getLocalBounds();
}

bool Player::getAccelerating()
{
	return accelerating;
}

float Player::getHspeed()
{
	return velX;
}

float Player::getVspeed()
{
	return velY;
}

bool Player::isGrounded()
{
	return grounded;
}

void Player::setSpeed(float value)
{
	speed = value;
}

float Player::getSpeed()
{
	return speed;
}

void Player::setHspeed(float value)
{
	velX = value;
}

void Player::setVspeed(float value)
{
	velY = value;
}

Score& Player::getScore()
{
	return score;
}

Health& Player::getHealth()
{
	return health;
}
