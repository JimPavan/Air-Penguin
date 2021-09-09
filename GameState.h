#pragma once
#include "stdafx.h"
#include "Player.h"
#include "Terrain.h"
#include "CameraFollower.h"
#include "GUI.h"

class GameState : public State
{
private:
	//Attributes
	Player player;
	Terrain terrain;
	CameraFollower camera;

	GUI gui;

	bool end;

public:
	//Constructors/Destructors
	GameState();

	//Functions
	void reset();
	void checkKeyboard();
	void checkEndGame();
	void update(float deltatime);
	void draw(sf::RenderWindow& window);

	//Getters/Setters
	bool getEndStatus();
};

