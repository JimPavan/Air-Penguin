#include "stdafx.h"

MenuState::MenuState()
{

}

void MenuState::checkTap()
{
	click = (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) ? true : false;
}

void MenuState::update(float deltatime)
{
	dynamicText.update(deltatime);

	checkTap();
}

void MenuState::draw(sf::RenderWindow& window)
{
	dynamicText.draw(window);
}

bool MenuState::isClick()
{
	return click;
}
