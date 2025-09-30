#include "Interceptor.h"
#include "Constants.h"


Texture2D Interceptor::interceptorTexture;


Interceptor::Interceptor(const Vector2& position, const Vector2& velocity)
	:Missile(position, velocity, constants::interceptorWidth, constants::interceptorHeight)
{
	boost = 170.0f;
	
	// if the texture was not loaded yet
	if (interceptorTexture.id == 0)
	{
		Image interceptor = LoadImage(constants::interceptorTexture);
		interceptorTexture = LoadTextureFromImage(interceptor);
		UnloadImage(interceptor);
	}
}



Interceptor::~Interceptor()
{
	UnloadTexture(interceptorTexture);
}




void Interceptor::update(const float dt)
{
	velocity.y += -boost * dt;
	position.x += velocity.x * dt;
	position.y += velocity.y * dt;
	angle = atan2(velocity.y, velocity.x) * RAD2DEG;
}



void Interceptor::draw() const
{
	DrawTextureEx(interceptorTexture, position, angle, 1.0f, WHITE);
	DrawLineV(hitLine.lineStart, hitLine.lineEnd, RED);
}



