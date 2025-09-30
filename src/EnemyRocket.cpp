#include "EnemyRocket.h"
#include "Constants.h"


Texture2D EnemyRocket::rocketTexture;



EnemyRocket::EnemyRocket(const Vector2& position, const Vector2& velocity)
	:Missile(position, velocity, constants::rocketWidth, constants::rocketHeight)
{
	gravity = 30.0f;

	// if the texture was not loaded yet
	if (rocketTexture.id == 0)
	{
		Image rocket = LoadImage(constants::rocketTexturePath);
		rocketTexture = LoadTextureFromImage(rocket);
		UnloadImage(rocket);
	}
}



EnemyRocket::~EnemyRocket()
{
	UnloadTexture(rocketTexture);
}




void EnemyRocket::update(const float dt)
{
	velocity.y += gravity * dt;
	position.x -= velocity.x * dt;
	position.y += velocity.y * dt;
	angle = -atan2(velocity.y, velocity.x) * RAD2DEG;
}




void EnemyRocket::draw() const
{
	DrawTextureEx(rocketTexture, position, angle, 1.0f, WHITE);
	DrawLineV(hitLine.lineStart, hitLine.lineEnd, RED);
}


