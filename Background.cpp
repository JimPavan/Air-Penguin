#include "stdafx.h"
#include "Background.h"

Background::Background()
{
	texture.loadFromFile("Resources//background.jpg");

	sprite = sf::Sprite(texture);
	sprite.setPosition(sf::Vector2f(0, 0));
	sprite.setScale(sf::Vector2f(0.6f, 0.6f));
}

void Background::update(float deltatime)
{
}

void Background::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
