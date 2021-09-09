#pragma once
#include "stdafx.h"
#include "Background.h"
#include "CameraFollower.h"

class Terrain
{
private:
	//Constants
	const static int H_WIDTH = 110;
	const static int V_HEIGHT = 140;
	const static int Y_BASE_POS = 450;
	const static int HEIGHT_MODULATION = 100;
	const static int CHUNCK_SIZE = 64;
	const float CURVE_PRECISION = 0.01f;

	int curveIndex;

	std::vector<sf::Vector2f> lines;
	std::vector<sf::Vector2f> curves;

	sf::Color bottomCurve;
	sf::Color topCurve;

	Background background;

	//Functions
	void loadTerrain(std::string filename);
	void addChunck();
	void updateTerrain(float x);
	void prepareDrawingLines();

public:
	// Constructors/Destructors
	Terrain();

	//Functions
	void initTerrain();
	void placePlayer(Player& player);
	int findLineIndex(float x);
	int findCurveIndex(float x);
	float getCurveAngle(float x);
	float getYCurve(float x);
	float getCurveAdvencement(float x);

	std::vector<sf::Vector2f> findCurvePlayerOn(float x);
	sf::Vector2f curve(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, float t);

	void update(Player& player, float deltatime);
	void draw(sf::RenderWindow &window);
	void drawBackground(sf::RenderWindow& window);
	void drawEmptyCurves(sf::RenderWindow& window);
	void drawEmptyLines(sf::RenderWindow& window);
	void drawFillCurves(sf::RenderWindow& window);
	void drawTopCurves(sf::RenderWindow& window);
};