#include "stdafx.h"

void Terrain::placePlayer(Player& player)
{
	player.setPosition(sf::Vector2f(lines[1].x, 0));
	float y = getYCurve(player.getPosition().x) - player.getSize().height / 2;
	player.setPosition(sf::Vector2f(lines[1].x, y));
}

int Terrain::findLineIndex(float x)
{
	int i = 0;
	while (lines[i].x < x)
		i += 1;

	return i - 1;
}

float Terrain::getCurveAngle(float x)
{
	std::vector<sf::Vector2f> line = findCurvePlayerOn(x);
	sf::Vector2f a = line[0];
	sf::Vector2f b = line[1];

	//Get adjacent side length, opposite side length and hypothenus length
	float adj = b.x - a.x;
	float opp = a.y - b.y;
	//Calculate angle by tan formula in radians
	float angle = atan(opp / adj);

	return angle;
}

int Terrain::findCurveIndex(float x)
{
	//static int curveIndex = 0;

	//Get positions of points a, b, c of the segment
	sf::Vector2f a = curves[curveIndex];
	sf::Vector2f b = curves[curveIndex + 1];
	sf::Vector2f c = curves[curveIndex + 2];
	//Get the percentage of the advencement of the player on the current curve
	float t = (x - a.x) / (c.x - a.x);

	if (t >= 1.f)
		curveIndex += 3;

	return curveIndex;
}

std::vector<sf::Vector2f> Terrain::findCurvePlayerOn(float x)
{
	std::vector<sf::Vector2f> line;

	int index = findCurveIndex(x);

	//Get the previous slope so it won't stuck the player because of proximity
	line.push_back(curves[index - 2]);
	line.push_back(curves[index]);

	return line;
}

float Terrain::getYCurve(float x)
{
	//Find index platform below the player
	int i = findCurveIndex(x);
	//Get positions of points a, b, c of the segment
	sf::Vector2f a = curves[i];
	sf::Vector2f b = curves[i + 1];
	sf::Vector2f c = curves[i + 2];
	//Get the percentage of the advencement of the player on the current curve
	float t = (x - a.x) / (c.x - a.x);
	//Get the y colliding value according to the advencement of the player on the curve
	float y = curve(a, b, c, t).y;

	return y;
}

float Terrain::getCurveAdvencement(float x)
{
	//Find index platform below the player
	int i = findCurveIndex(x);
	//Get positions of points a, b, c of the segment
	sf::Vector2f a = curves[i];
	sf::Vector2f b = curves[i + 1];
	sf::Vector2f c = curves[i + 2];
	//Get the percentage of the advencement of the player on the current curve
	float t = (x - a.x) / (c.x - a.x);

	return t;
}

sf::Vector2f Terrain::curve(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, float t)
{
	//Create curve from point p1 to point p3 with anchor point p2 by time t
	float x = pow(1 - t, 2) * p1.x + 2 * (1 - t) * t * p2.x + pow(t, 2) * p3.x;
	float y = pow(1 - t, 2) * p1.y + 2 * (1 - t) * t * p2.y + pow(t, 2) * p3.y;

	return sf::Vector2f(x, y);
}

void Terrain::update(Player& player, float deltatime)
{
	background.update(deltatime);
	updateTerrain(player.getPosition().x);

	float x = player.getPosition().x;
	float y = getYCurve(x);
	float angle = getCurveAngle(x);
	float curveAdvance = getCurveAdvencement(x);
	float height = player.getSize().height;
	float rotAngle = -atan(angle) * 180 / 3.14f;

	//Check if the player is on the ground
	if (player.getPosition().y + height / 2 > y)
	{
		//Break speed momentum if the player dives to the climb side of the slope
		if (!player.isGrounded() && player.getVspeed() > 0 && angle > 0)
		{
			player.setSpeed(player.getSpeed() / 3.5f);
			player.setHspeed(player.getHspeed() / 3.5f);
			player.setVspeed(player.getVspeed() / 3.5f);
		}

		//Make the player follow the cliff by angle and expulse it when leaves the floor
		if (!(player.getVspeed() < 0 && angle < 0)) {
			player.stopFalling();
			player.moveByAngle(-angle);
			player.setPosition(sf::Vector2f(player.getPosition().x, y - height / 2));
			player.smoothRotate(rotAngle, deltatime, player.ROTATION_SPEED_GROUND);
		}
	}
	else
	{
		//Make player fall down when in the air
		player.smoothRotate(player.MAX_ROTATION_IN_AIR, deltatime, player.ROTATION_SPEED_IN_AIR);
		player.startFalling();
	}

	//Get the player back on the ground if close to the slope
	if (player.getPosition().y + height / 2 + player.AMOUNT_SLIDE_TOUCH >= y && curveAdvance >= 0.05f && curveAdvance <= 0.95f)
	{
		player.setPosition(sf::Vector2f(player.getPosition().x, y - height / 2));
		player.stopFalling();
	}
}

void Terrain::initTerrain()
{
	//In case of the reset of the terrain -> new game
	lines.clear();
	curves.clear();

	curveIndex = 0;

	bottomCurve = sf::Color(200, 200, 200);
	topCurve = sf::Color(50, 50, 50);

	for (int i = 0; i < CHUNCK_SIZE; i++)
		addChunck();

	prepareDrawingLines();
}

void Terrain::loadTerrain(std::string filename)
{
	//Open file test terrain
	std::ifstream file(filename);
	float x, y;

	if (file.is_open())
	{
		std::string line;

		while (std::getline(file, line))
		{
			sscanf_s(line.c_str(), "%f %f", &x, &y);
			lines.push_back(sf::Vector2f(x, y));
		}

		file.close();
	}
}

void Terrain::addChunck()
{
	//Create terrain using random height modulations

	static int side = -1;

	if (lines.size() == 0)
	{
		lines.push_back(sf::Vector2f(0, Y_BASE_POS));
		lines.push_back(sf::Vector2f(H_WIDTH, Y_BASE_POS + side * (V_HEIGHT + std::rand() % HEIGHT_MODULATION)));
		lines.push_back(sf::Vector2f(2 * H_WIDTH, Y_BASE_POS));
	}
	else
	{
		lines.push_back(sf::Vector2f(lines[lines.size() - 1].x + H_WIDTH, Y_BASE_POS + side * (V_HEIGHT + std::rand() % HEIGHT_MODULATION)));
		lines.push_back(sf::Vector2f(lines[lines.size() - 1].x + H_WIDTH, Y_BASE_POS));
	}

	side *= -1;
}

void Terrain::updateTerrain(float x)
{
	/*static bool t = true;

	int index = findLineIndex(x);

	if (index == 9 && t)
	{
		
		t = false;
		lines.erase(lines.begin(), lines.begin() + 4);
		curves.clear();
		prepareDrawingLines();
	}

	std::cout << index << std::endl;*/
	//std::cout << curves.size() << std::endl;
	/*if (index == 2)
	{
		addChunck();

		lines.erase(lines.begin(), lines.begin() + 2);
		curves.clear();
		prepareDrawingLines();
	}*/
}

Terrain::Terrain()
{
	//loadTerrain("terrainTest.terrain");

	initTerrain();
}

/*---------------------Drawing---------------------*/
void Terrain::prepareDrawingLines()
{
	//Prepare the positions to the curved terrain
	for (int i = 0; i <= lines.size() - 3; i += 2)
	{
		sf::Vector2f p1 = lines[i];
		sf::Vector2f p2 = lines[i + 1];
		sf::Vector2f p3 = lines[i + 2];

		//Curve the slope with p1, p3 side points and p2 anchor point
		for (float t = 0; t <= 1; t += CURVE_PRECISION)
		{
			sf::Vector2f p = curve(p1, p2, p3, t);
			curves.push_back(p);
		}
	}
}

void Terrain::draw(sf::RenderWindow &window)
{
	//drawEmptyLines(window);
	//drawEmptyCurves(window);
	drawBackground(window);
	drawFillCurves(window);
	drawTopCurves(window);
}

void Terrain::drawBackground(sf::RenderWindow& window)
{
	sf::View v = window.getView();
	window.setView(window.getDefaultView());
	background.draw(window);
	window.setView(v);
}

void Terrain::drawEmptyCurves(sf::RenderWindow& window)
{
	/*Draw curved line*/

	//curves if draw curves lines if draw lines
	sf::VertexArray vertices = sf::VertexArray(sf::LinesStrip, curves.size());

	for (int i = 0; i < curves.size(); i++)
	{
		vertices[i].position = curves[i];
		vertices[i].color = sf::Color(243, 119, 53);
	}

	window.draw(vertices);
}

void Terrain::drawEmptyLines(sf::RenderWindow& window)
{
	/*Draw curved line*/

	//curves if draw curves lines if draw lines
	sf::VertexArray vertices = sf::VertexArray(sf::LinesStrip, lines.size());

	for (int i = 0; i < lines.size(); i++)
	{
		vertices[i].position = lines[i];
		vertices[i].color = sf::Color::Blue;
	}

	window.draw(vertices);
}

void Terrain::drawFillCurves(sf::RenderWindow& window)
{
	/*Draw the whole cliffs with solid color/texture*/

	sf::VertexArray vertices = sf::VertexArray(sf::TrianglesStrip, curves.size());

	for (int i = 0; i < curves.size() - 1; i += 2)
	{
		vertices[i].position = curves[i];
		vertices[i + 1].position = sf::Vector2f(curves[i].x, SCREEN_HEIGHT);

		vertices[i].color = bottomCurve;
		vertices[i + 1].color = topCurve;
	}

	vertices[vertices.getVertexCount() - 1].position = vertices[vertices.getVertexCount() - 2].position;

	window.draw(vertices);
}

void Terrain::drawTopCurves(sf::RenderWindow& window)
{
	/*Draw the in-between color/texture*/

	sf::VertexArray vertices = sf::VertexArray(sf::TrianglesStrip, curves.size());

	for (int i = 0; i < curves.size() - 1; i += 2)
	{
		vertices[i].position = curves[i];
		vertices[i + 1].position = sf::Vector2f(curves[i].x, curves[i].y + 5);

		vertices[i].color = bottomCurve;
		vertices[i + 1].color = topCurve;
	}

	vertices[vertices.getVertexCount() - 1].position = vertices[vertices.getVertexCount() - 2].position;

	window.draw(vertices);
}
