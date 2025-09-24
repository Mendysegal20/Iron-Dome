#pragma once
#include <raylib.h>
#include <math.h>


class Missile
{

public:

	Vector2 position;
	Vector2 velocity;
	Vector2 missileBody[5];
	
	Missile(const Vector2& position, const Vector2& velocity);

	void rotate(float angle);

};





