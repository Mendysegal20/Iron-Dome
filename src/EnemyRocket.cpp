#include "EnemyRocket.h"
#include "Constants.h"


Texture2D EnemyRocket::rocketTexture = { 0 };




EnemyRocket::EnemyRocket(const Vector2& position, const Vector2& velocity)
	:Missile(position, Vector2{ -1, 1 }, velocity, 
		constants::rocketWidth, constants::rocketHeight)
{
	gravity = 45.0f;
	//loadAssets(rocketTexture, constants::rocketTexturePath);
}






void EnemyRocket::loadRocketTexture()
{
	if (rocketTexture.id == 0)
	{
		Image img = LoadImage(constants::rocketTexturePath);
		rocketTexture = LoadTextureFromImage(img);
		UnloadImage(img);
	}
}





void EnemyRocket::unloadRocketTexture()
{
	if (rocketTexture.id != 0) // if the texture is loaded
	{
		UnloadTexture(rocketTexture);
		rocketTexture.id = 0;
	}
}


//EnemyRocket::~EnemyRocket()
//{
//	UnloadTexture(rocketTexture);
//}




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


float EnemyRocket::getGravity() const
{
	return gravity;
}


Vector2 EnemyRocket::getVelocity() const
{
	return velocity;
}


