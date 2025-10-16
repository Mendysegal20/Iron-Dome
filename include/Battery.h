#pragma once
#include "Interceptor.h"
#include "EnemyRocket.h"
//#include "Radar.h"
#include <vector>
#include "Constants.h"
#include <iostream>


class Battery
{
public:
	
	//Battery()
	//{
	//	position = { 40, 640 };
	//	
	//	for(int i = 0; i < 5; ++i)
	//	{
	//		// build 5 interceptors in the battery without copying them
	//		// like with push_back(Interceptor(...))
	//		interceptors.emplace_back(
	//			Interceptor(Vector2{ position.x + 5 * i, position.y },
	//						Vector2{ 470.0f, 300.0f })
	//		);
	//	}
	//}

	void update(const float dt)
	{
		/*for (Interceptor& interceptor : interceptors)
		{
			interceptor.update(dt);
			interceptor.draw();

			if(interceptor.state == Launched && interceptor.targetPosition != nullptr)
			{
				interceptor.chase(dt);
			}
		}*/
		
	}
	
	void lanchInterceptor(const EnemyRocket& enemy, const float dt)
	{
		/*for(Interceptor& interceptor : interceptors)
		{
			if (interceptor.state == Idle)
			{
				interceptor.targetPosition = &enemy.getHitLine();
				interceptor.state = Launched;
				break;
			}
		}*/
	}


	static bool isThreat(const EnemyRocket& enemy)
	{
		/*
			the formula of motion under gravity is:
			y(t) = y0 + vy * t + 0.5 * gt^2

			y(t) means the height of the rocket at time t
			y0 means the initial height of the rocket
			vy means the vertical component of the rocket's velocity
			g means the gravity
		*/
		
		float a = 0.5f * enemy.getGravity();
		float b = enemy.getVelocity().y;
		float c = enemy.getHitLine().lineEnd.y - constants::ground;
		float discriminant = b * b - 4 * a * c;


		if (discriminant < 0.0f)
			return false; // No real solutions, the rocket will not hit the ground

		float t1 = (-b + sqrtf(discriminant)) / (2 * a);
		float t2 = (-b - sqrtf(discriminant)) / (2 * a);
		float t = -1.0f;

		if (t1 <= 0.0f && t2 <= 0.0f)
			return false;

		if (t1 > 0.0f && t2 > 0.0f)
			t = std::min(t1, t2);

		else
			t = (t1 > 0.0f) ? t1 : t2;

		if (t <= 0.0f)
			return false; // Both solutions aren't positive, the rocket will not hit the ground

		
		//float bufferTime = 0.3f;
		float impactX = enemy.getHitLine().lineEnd.x + enemy.getVelocity().x * t; //(t * bufferTime);


		if ((impactX < constants::cityRightBoundary.x
			&& impactX > constants::cityLeftBoundary.x))
				return true;

		return false;
	}

//private:

	/*std::vector<Interceptor> interceptors;
	Vector2 position;*/
};

