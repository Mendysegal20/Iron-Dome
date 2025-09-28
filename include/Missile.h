#pragma once
#include <raylib.h>
#include <math.h>


class Missile
{

public:

	Vector2 position;
	Vector2 velocity;
	//Rectangle hitbox;
	Vector2 center;
	Missile(const Vector2& position, const Vector2& velocity, 
		const float width, const float height);
	//void draw() {};
};





