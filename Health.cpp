#include "stdafx.h"
#include "Health.h"

Health::Health()
{
	health = MAX_HEALTH;
}

void Health::update(float deltatime, float posx, float posy)
{
	if (posx >= X_HEALTH_THRESHOLD)
	{
		int side = 1;

		//player below the threshold looses health, above gains health
		if (posy > Y_HEALTH_THRESHOLD)
			side = -1;

		//Heal the player/kill the player
		health += side * LIFE_GAIN * deltatime;

		//Bound the health
		if (health > MAX_HEALTH)
			health = MAX_HEALTH;
		else if (health < 0)
			health = 0;
	}
}

float Health::getHealth()
{
	return health;
}

float Health::getHealthRatio()
{
	return health / MAX_HEALTH;
}

void Health::setHealth(float ratio)
{
	health = ratio * MAX_HEALTH;
}
