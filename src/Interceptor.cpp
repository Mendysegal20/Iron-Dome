#include "Interceptor.h"
#include "Constants.h"


Texture2D Interceptor::interceptorTexture = { 0 };


Interceptor::Interceptor(const Vector2& position, const Vector2& velocity)
	:Missile(position, Vector2{ 1, -1 }, velocity, constants::interceptorWidth, 
		constants::interceptorHeight)
{
	boost = 0.0f;
	isEnemyClose = false;
	loadAssets(interceptorTexture, constants::interceptorTexturePath);
}



Interceptor::~Interceptor()
{
	UnloadTexture(interceptorTexture);
}




void Interceptor::update(const float dt)
{
	applyForces(dt);
	rotateHitLine();
	
	
	/*velocity.y += -boost * dt;
	position.x += velocity.x * dt;
	position.y += velocity.y * dt;
	angle = atan2f(velocity.y, velocity.x) * RAD2DEG;*/
}



void Interceptor::draw() const
{
	DrawTextureEx(interceptorTexture, position, angle, 1.0f, WHITE);
	DrawLineV(hitLine.lineStart, hitLine.lineEnd, RED);
}



void Interceptor::applyForces(const float dt)
{
	velocity.y += -boost * dt;
}



void Interceptor::chase(const Line& targetPos, const float dt)
{
	Vector2 targetHead = {targetPos.lineEnd.x,
		targetPos.lineEnd.y };
	
	Vector2 toTarget = { targetHead.x - hitLine.lineEnd.x, targetHead.y - hitLine.lineEnd.y };

	float distance = sqrtf(toTarget.x * toTarget.x + toTarget.y * toTarget.y);

	if (distance < 0.01f)
		return;

	toTarget.x /= distance;
	toTarget.y /= distance;

	/*if (distance < 10.0f)
		isEnemyClose = true;*/

	//float dot = velocity.x * toTarget.x + velocity.y * toTarget.y;

	
	
	if (!(targetHead.x - hitLine.lineEnd.x - 15 <= 0.0f) && 
		!(hitLine.lineEnd.y - targetHead.y - 5 <= 0.0f))
	{
		float speed = sqrtf(velocity.x * velocity.x + velocity.y * velocity.y);
		velocity.x = toTarget.x * speed;
		velocity.y = toTarget.y * speed;
	}
	
	angle = atan2f(velocity.y, velocity.x) * RAD2DEG;
	position.x += velocity.x * dt;
	position.y += velocity.y * dt;
}



void Interceptor::checkForCollition(const Line& enemy)
{
	if (CheckCollisionLines(hitLine.lineStart, hitLine.lineEnd,
		enemy.lineStart, enemy.lineEnd, NULL))
			DrawText("Collision!", 400, 100, 30, BLUE);
}




