#include "stdafx.h"
#include "GameState.h"

GameState::GameState() : 
	camera(SCREEN_WIDTH, SCREEN_HEIGHT, player)
{
	//Make the game (level generation) random
	std::srand(std::time(nullptr));

	//Place the player in starting position
	terrain.placePlayer(player);

	//Set score start
	player.getScore().setStartOffset(player.getSprite().getPosition().x);

	//The player is not dead nor the user wants to leave the game
	end = false;
}

void GameState::reset()
{
	//Player reset
	player.reset();
	player.getScore().setStartOffset(player.getSprite().getPosition().x);
	player.getHealth().setHealth(1);

	//Terrain reset
	terrain.initTerrain();
	terrain.placePlayer(player);

	//Camera reset
	camera.setDefault();

	//GameState reset
	end = false;
}

void GameState::checkKeyboard()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		player.setAccelerating(true);
	else
		player.setAccelerating(false);
}

void GameState::checkEndGame()
{
	if (player.getHealth().getHealth() <= 0)
	{
		end = true;
	}
}

void GameState::update(float deltatime)
{
	//Update logic
	checkEndGame();
	checkKeyboard();

	terrain.update(player, deltatime);
	player.update(deltatime);
	camera.update(deltatime);

	//Update GUI
	gui.update(player.getScore(), player.getHealth());
}

void GameState::draw(sf::RenderWindow& window)
{
	//Draw player and terrain stuff
	window.setView(camera.getView());
	terrain.draw(window);
	player.draw(window);

	//Draw GUI
	window.setView(window.getDefaultView());
	gui.draw(window);
}

bool GameState::getEndStatus()
{
	return end;
}
