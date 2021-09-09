#include "stdafx.h"
#include "GUI.h"

GUI::GUI()
{
	//Positions
	fontSize = 15;
	yPos = 10;
	airTextX = 10;
	scoreTextX = SCREEN_WIDTH - 50;

	//Load font
	font.loadFromFile("ice_font.otf");

	//Air text
	airText.setFont(font);
	airText.setString("Air:");
	airText.setCharacterSize(fontSize);

	//Score text
	scoreText.setFont(font);
	scoreText.setString("");
	scoreText.setCharacterSize(fontSize);
}

void GUI::update(Score& score, Health& health)
{
	//Update score text
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2) << score.getScore();

	scoreText.setString(ss.str());
	scoreText.setPosition(scoreTextX, yPos);

	//Update air text
	airText.setPosition(airTextX, yPos);

	//Update air gauge
	gauge.update(health.getHealthRatio());
}

void GUI::draw(sf::RenderWindow& window)
{
	window.draw(airText);
	window.draw(scoreText);
	
	gauge.draw(window);
}
