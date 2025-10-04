#include "EnemyRocket.h"
#include "Constants.h"


Texture2D EnemyRocket::rocketTexture = { 0 };



EnemyRocket::EnemyRocket(const Vector2& position, const Vector2& velocity)
	:Missile(position, Vector2{ -1, 1 }, velocity, 
		constants::rocketWidth, constants::rocketHeight)
{
	gravity = 5.0f;
	loadAssets(rocketTexture, constants::rocketTexturePath);
}



EnemyRocket::~EnemyRocket()
{
	UnloadTexture(rocketTexture);
}




//void EnemyRocket::update(const float dt)
//{
//	velocity.y += gravity * dt;
//	position.x += velocity.x * dt;
//	position.y += velocity.y * dt;
//	angle = atan2f(velocity.y, velocity.x) * RAD2DEG;
//}




void EnemyRocket::draw() const
{
	DrawTextureEx(rocketTexture, position, angle, 1.0f, WHITE);
	DrawLineV(hitLine.lineStart, hitLine.lineEnd, RED);
}



void EnemyRocket::applyForces(const float dt)
{
	velocity.y += gravity * dt;
}



EnemyRocket::Line EnemyRocket::getHitLine()
{
	return hitLine;
}

