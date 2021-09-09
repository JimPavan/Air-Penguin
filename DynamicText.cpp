#include "stdafx.h"

DynamicText::DynamicText()
{	//Load font
	font.loadFromFile("ice_font.otf");

	//Setup text
	tapText.setFont(font);
	tapText.setString("tap to play");
	tapText.setCharacterSize(56);
	tapText.setOrigin(tapText.getLocalBounds().width / 2, tapText.getLocalBounds().height / 2);
	tapText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	//Setup opacity vars
	opacity = 255;
	speedOpacity = 110;
	bound = 50;
	sideChange = 1;
}

void DynamicText::update(float deltatime)
{
	opacity += sideChange * speedOpacity * deltatime;

	if (opacity < bound)
	{
		opacity = bound;
		sideChange *= -1;
	}
	else if (opacity > 255)
	{
		opacity = 255;
		sideChange *= -1;
	}

	tapText.setFillColor(sf::Color(100, 100, 100, opacity));
}

void DynamicText::draw(sf::RenderWindow& window)
{
	window.draw(tapText);
}
