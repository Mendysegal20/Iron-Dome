#pragma once
#include <cmath>
#include <iostream>
#include "Interceptor.h"
#include "EnemyRocket.h"
#include "Constants.h"




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
	
	void evaluateThreat(Interceptor& interceptor, const EnemyRocket& enemy);

private:

	bool isThreat(const EnemyRocket& enemy);
};

