#pragma once

class Camera
{
protected:
	//Attributes
	sf::View view;

	float width;
	float height;

public:
	//Constructors/Destructors
	Camera();
	Camera(float width, float height);

	//Functions
	void setDefault();
	void update(float deltatime);

	//Getters/Setters
	sf::View getView();
	void setView(sf::View v);
};

