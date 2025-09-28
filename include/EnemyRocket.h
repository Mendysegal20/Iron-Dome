#pragma once
#include "Missile.h"
#define PI 3.14159265359



class EnemyRocket : public Missile
{

public:

	EnemyRocket(const Vector2& position, const Vector2& velocity)
		:Missile(position, velocity, 90, 8)
	{
		gravity = 25.0f;
		Image rocket = LoadImage("assets/missile4.png");
		rocketTexture = LoadTextureFromImage(rocket);
		UnloadImage(rocket);
	}


	void update(const float dt)
	{
		// we multiply only the x velocity because the y is calculated 
		// from the quadratic equation, meaning position.y is dependent on position.x alone
		
		velocity.y += gravity * dt;
		position.x -= velocity.x * dt;
		position.y += velocity.y * dt;

		angle = -atan2(velocity.y, velocity.x) * DEG2RAD;
	}


	void draw()
	{
		DrawTextureEx(rocketTexture, position, angle, 1.0f, WHITE);
	}
	
private:
	float gravity;	
	float angle = 0.0f;
	Texture2D rocketTexture;
};






