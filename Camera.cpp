#include "stdafx.h"

Camera::Camera() : width(SCREEN_WIDTH), height(SCREEN_HEIGHT)
{
	
}

Camera::Camera(float width, float height) : width(width), height(height)
{
	setDefault();
}

void Camera::setDefault()
{
	view.reset(sf::FloatRect(0, 0, width, height));
	view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	view.zoom(1.f);
}

void Camera::update(float deltatime)
{
}

sf::View Camera::getView()
{
	return view;
}

void Camera::setView(sf::View v)
{
	view = v;
}
