#include "Interceptor.h"
#include "Constants.h"


Texture2D Interceptor::interceptorTexture = { 0 };



Interceptor::Interceptor(const Vector2& position, const Vector2& velocity)
	:Missile(position, Vector2{ 1, -1 }, velocity, constants::interceptorWidth, 
		constants::interceptorHeight)
{
	boost = 0.0f;
}





void Interceptor::loadInterceptorTexture()
{
	if (interceptorTexture.id == 0)
	{
		Image img = LoadImage(constants::interceptorTexturePath);
		interceptorTexture = LoadTextureFromImage(img);
		UnloadImage(img);
	}
}




void Interceptor::unloadInterceptorTexture()
{
	if (interceptorTexture.id != 0) // if the texture is loaded
	{
		UnloadTexture(interceptorTexture);
		interceptorTexture.id = 0;
	}
}





void Interceptor::update(const Line& enemyPos, const float dt)
{

	
	
	switch (state)
	{
		case Idle:
			// do nothing for now
			break;

		case Launched:
			applyForces(dt);
			rotateHitLine();
			chase(enemyPos, dt);
			checkForCollition(enemyPos);
			break;
		
		case HitTarget:
			// do nothing for now
			break;
	}
	
	/*if (state == Launched)
	{
		applyForces(dt);
		rotateHitLine();
	}*/

	/*else if (state == Exploding)
	{
		blastHead.currentTime += dt;

		if(blastHead.currentTime >= blastHead.lifetime)
			state = Destroyed;
	}*/

	/*velocity.y += -boost * dt;
	position.x += velocity.x * dt;
	position.y += velocity.y * dt;
	angle = atan2f(velocity.y, velocity.x) * RAD2DEG;*/
}



void Interceptor::draw() const
{
	
	if (state == Launched)
	{
		DrawTextureEx(interceptorTexture, position, angle, 1.0f, WHITE);
		DrawLineV(hitLine.lineStart, hitLine.lineEnd, RED);
	}
}



void Interceptor::applyForces(const float dt)
{
	velocity.y += -boost * dt;
}


Vector2 Interceptor::getHeadPosition() const
{
	return hitLine.lineEnd;
}



InterceptorState Interceptor::getState() const
{
	return state;
}


void Interceptor::lunch()
{
	state = Launched;
}




void Interceptor::chase(const Line& targetPos, const float dt)
{

	//if (position.x < 80.0f || position.y > 600.0f)
	//{
	//	float launchAngle = -60.0f * DEG2RAD; // בערך 60 מעלות כלפי מעלה
	//	float launchSpeed = 450.0f; // מהירות התחלתית

	//	velocity.x = cosf(launchAngle) * launchSpeed;
	//	velocity.y = sinf(launchAngle) * launchSpeed;

	//	angle = launchAngle * RAD2DEG;

	//	position.x += velocity.x * dt;
	//	position.y += velocity.y * dt;
	//	return;
	//}
		

	// the target's head position
	Vector2 targetHead = { targetPos.lineEnd.x, targetPos.lineEnd.y };
	
	// direction vector from interceptor to target
	Vector2 toTarget = { targetHead.x - hitLine.lineEnd.x, 
						 targetHead.y - hitLine.lineEnd.y };

	// distance to the target with Pythagorean theorem: sqrt((x1 - x2)^2 + (y1 - y2)^2)
	float distance = sqrtf(toTarget.x * toTarget.x + toTarget.y * toTarget.y);

	// if the distance is very small, no need to continue calculating
	if (distance < 0.01f)
		return;

	/* normalize the direction vector so its length is 1
	   it means the coordinates of the vector will be between -1 and 1. 
	   we normalize because we only need the direction, not the magnitude
	   normalization is done by dividing each component by the vector's magnitude (distance)
	   and later we will multiply it by constnt speed to get the velocity vector 
	   NOTE: if we don't normalize, the velocity later will not be constant and will vary based on the distance
			 to the target which is changing every frame */
	toTarget.x /= distance;
	toTarget.y /= distance;

	
	//float dot = velocity.x * toTarget.x + velocity.y * toTarget.y;
	
	/* if the interceptor is not close enough to the target,
	   adjust its velocity and angle. But if the interceptor
	   is close enough with a little margin of 15 pixels in x and 5 pixels in y
	   to the target, do not adjust its velocity and angle */
	if (!(targetHead.x - hitLine.lineEnd.x - 15 <= 0.0f) && 
		!(hitLine.lineEnd.y - targetHead.y - 5 <= 0.0f))
	{
		// the speed is the magnitude of the velocity vector
		float speed = sqrtf(velocity.x * velocity.x + velocity.y * velocity.y);
		
		/* multiply the normalized direction vector by the speed
		   and set it as the new velocity */
		velocity.x = toTarget.x * speed;
		velocity.y = toTarget.y * speed;
	}
	
	// update the angle and position
	angle = atan2f(velocity.y, velocity.x) * RAD2DEG;
	position.x += velocity.x * dt;
	position.y += velocity.y * dt;
}






void Interceptor::checkForCollition(const Line& enemy)
{
	if (CheckCollisionLines(hitLine.lineStart, hitLine.lineEnd,
		enemy.lineStart, enemy.lineEnd, NULL))
			state = HitTarget;
}

