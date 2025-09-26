#pragma once
#include "Missile.h"
#define PI 3.14159265359


class EnemyRocket : public Missile
{

public:

	EnemyRocket(const Vector2& position, const Vector2& velocity)
		:Missile(position, velocity)
	{
		gravity = 10.0f;
		
		float width = 10.0f;
		float height = 70.0f;
		float tipHeight = 20.0f;

		// יחסית לשפיץ (tip)
		relativeBody[0] = { 0.0f, 0.0f };          // tip
		relativeBody[1] = { -width / 2, tipHeight };
		relativeBody[2] = { -width / 2, height };
		relativeBody[3] = { width / 2, height };
		relativeBody[4] = { width / 2, tipHeight };
	}

	void update(const float dt)
	{

		velocity.y += gravity * dt;

		position.x -= velocity.x * dt;
		position.y += velocity.y * dt;
		
		for (int i = 0; i < 5; i++)
		{
			missileBody[i].x = relativeBody[i].x + position.x;
			missileBody[i].y = relativeBody[i].y + position.y;
		}

		//position = missileBody[0];
				

		float angle = -atan2(velocity.y, velocity.x) -0.5 * PI;

		rotate(angle);


		
		// we multiply only the x velocity because the y is calculated 
		// from the quadratic equation, meaning position.y is dependent on position.x alone
		
		//position.x += velocity.x * dt;

		
		
		//position.y = a * (position.x * position.x) + b * position.x + c;


		//float dx = velocity.x;
		//float dy = 2 * a * position.x + b; // derivative of the quadratic equation
		//float angle = atan2(dy, dx); // angle in radians
		//
		//rotate(angle);


		/*for (int i = 0; i < 5; i++) added
		{
			missileBody[i].x += velocity.x * dt;
		}*/
	}
	
private:
	//float a, b, c; // coefficients for the quadratic equation y = ax^2 + bx + c
	float gravity;
	Vector2 relativeBody[5];
};






