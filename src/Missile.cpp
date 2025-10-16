#include "Missile.h"



Missile::Missile(const Vector2& position, const Vector2& direction, 
	const Vector2& velocity, const float width, const float height)
{
	this->angle = 0.0f;
	this->position = position;
	this->direction = direction;
	
	this->velocity.x = velocity.x * direction.x;
	this->velocity.y = velocity.y * direction.y;
	

	this->spriteSize = { width, height };
	this->center = { position.x + width / 2.0f,
		position.y + height / 2.0f };
	
	this->hitLine.lineStart = {position.x, position.y / 2.0f};
	this->hitLine.lineEnd = {position.x - width, position.y / 2.0f};
}




void Missile::update(const float dt)
{
	applyForces(dt);
	position.x += velocity.x * dt;
	position.y += velocity.y * dt;
	angle = atan2f(velocity.y, velocity.x) * RAD2DEG;
	rotateHitLine();
}




//void Missile::loadAssets(Texture2D& texture, const char* texturePath)
//{
//	if (texture.id == 0)
//	{
//		Image img = LoadImage(texturePath);
//		texture = LoadTextureFromImage(img);
//		UnloadImage(img);
//	}
//}




void Missile::rotateHitLine()
{
	/*
        Rotate a line inside a sprite around the sprite's top-left corner.

        Parameters:
        - start, end: references to the line's start and end points (output)
        - spritePos: the start position of the sprite wech is the top-left corner of the sprite
        - spriteSize: width and height of the sprite
        - angle: rotation angle in degrees

        How it works:
        1. Define the line's start and end points relative to the sprite's top-left corner.
        2. Convert the rotation angle to radians.
        3. Rotate each point around the origin (0,0) using the standard 2D rotation formula:
              x' = cos(a) * x - sin(a) * y
              y' = sin(a) * x + cos(a) * y
               (here, x and y are offsets from the sprite's top-left corner
                for example if the sprite position starts at (300,300) and the point we
                want to rotate is at (400,400), then the ofsset to that point would be (100,100)
                and we will calculate the point (100,100) with the formula and then we will add
                the sprite's starts position (300,300) to have the point rotated according
                to the origin (300,300) and not (0,0))
        4. Add spritePos to convert the rotated points to absolute screen coordinates.
    */
	
	
	Vector2 oldStart = { 0, spriteSize.y / 1.5f };
	Vector2 oldEnd = { spriteSize.x, spriteSize.y / 2.0f };


	const float radian = angle * DEG2RAD;
	
	hitLine.lineStart.x = position.x + oldStart.x * cosf(radian) - oldStart.y * sinf(radian);
	hitLine.lineStart.y = position.y + oldStart.x * sinf(radian) + oldStart.y * cosf(radian);

	hitLine.lineEnd.x = position.x + oldEnd.x * cosf(radian) - oldEnd.y * sinf(radian);
	hitLine.lineEnd.y = position.y + oldEnd.x * sinf(radian) + oldEnd.y * cosf(radian);
}
