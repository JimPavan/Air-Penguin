#include "stdafx.h"

Gauge::Gauge()
{
	//Setup start positions
	x = 45;
	y = 13;
	width = 120;
	height = 12;

	//Setup color of rects
	backColor = sf::Color(50, 50, 50, 200);
	frontColor = sf::Color(20, 20, 200, 200);

	//Setup	back rectangle
	backRect.setPosition(x, y);
	backRect.setSize(sf::Vector2f(width, height));
	backRect.setFillColor(backColor);

	//Setup front rectangle
	frontRect.setPosition(x, y);
	frontRect.setSize(sf::Vector2f(width, height));
	frontRect.setFillColor(frontColor);
}

void Gauge::update(float ratio)
{
	frontRect.setSize(sf::Vector2f(width * ratio, height));
}

void Gauge::draw(sf::RenderWindow& window)
{
	window.draw(backRect);
	window.draw(frontRect);
}
