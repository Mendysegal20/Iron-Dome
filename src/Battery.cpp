#include "Battery.h"
#include "SoundManager.h"






void Battery::evaluateThreat(Interceptor& interceptor, const EnemyRocket& enemy)
{
	if (isThreat(enemy) && interceptor.getState() == InterceptorState::Idle)
	{
		SoundManager::playLaunchSound();
		interceptor.lunch();
	}
		
}






bool Battery::isThreat(const EnemyRocket& enemy)
{
	if (enemy.getHitLine().lineEnd.y >= constants::ground)
		return false; // already on the ground

	if (enemy.getHitLine().lineEnd.x < constants::cityLeftBoundary.x)
		return false;

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








