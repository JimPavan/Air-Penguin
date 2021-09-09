#include "stdafx.h"
#include "Utils.h"

float lerp(float a, float b, float t)
{
	//Lerp from a to b by t

	return a + (b - a) * t;
}
