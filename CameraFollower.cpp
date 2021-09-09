#include "stdafx.h"

CameraFollower::CameraFollower(float width, float height, Player& player) : Camera(width, height), player(player)
{

}

void CameraFollower::update(float deltatime)
{
	view.setCenter(sf::Vector2f(player.getPosition().x - player.getSize().width + width / 2, view.getCenter().y));
}

sf::Vector2f CameraFollower::getPosition()
{
	//Return topleft position
	float x = player.getPosition().x + player.getSize().width - width / 2;
	float y = view.getCenter().y;

	return sf::Vector2f(x, y);
}
