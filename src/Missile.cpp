#include "Missile.h"



Missile::Missile(const Vector2& position, const Vector2& velocity, 
	const float width, const float height)
{
	this->position = position;
	this->velocity = velocity;
	this->center = { position.x + width / 2.0f, position.y + height / 2.0f };
	//this->hitbox = hitbox;
}






