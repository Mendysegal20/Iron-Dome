#include "Missile.h"



Missile::Missile(const Vector2& position, const Vector2& velocity, 
	const float width, const float height)
{
	this->angle = 0.0f;
	this->position = position;
	this->velocity = velocity;
	this->spriteSize = { width, height };
	this->center = { position.x + width / 2.0f,
		position.y + height / 2.0f };
	
	this->hitLine.lineStart = {0, 0};
	this->hitLine.lineEnd = {0, 0};
}



void Missile::rotateHitLine()
{
	Vector2 oldStart = { 0, spriteSize.y / 1.5f };
	Vector2 oldEnd = { spriteSize.x, spriteSize.y / 2.0f };


	const float radian = angle * DEG2RAD;
	
	hitLine.lineStart.x = position.x + oldStart.x * cosf(radian) - oldStart.y * sinf(radian);
	hitLine.lineStart.y = position.y + oldStart.x * sinf(radian) + oldStart.y * cosf(radian);

	hitLine.lineEnd.x = position.x + oldEnd.x * cosf(radian) - oldEnd.y * sinf(radian);
	hitLine.lineEnd.y = position.y + oldEnd.x * sinf(radian) + oldEnd.y * cosf(radian);
}



