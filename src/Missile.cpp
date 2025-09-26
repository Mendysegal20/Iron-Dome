#include "Missile.h"



Missile::Missile(const Vector2& position, const Vector2& velocity):
	position(position), velocity(velocity), center({ 0,0 })
{

	float tipPointX = position.x; // center x of the missile (at the tip)
	float tipPointY = position.y; // center y of the missile (at the tip)
	float width = 10; // the width of the missile
	float height = 70; // the height of the missile
	float tipHeight = 20; // the height of the tip of the missile


	missileBody[0] = { tipPointX, tipPointY }; // tip point
	missileBody[1] = { tipPointX - width / 2, tipPointY + tipHeight }; // left point of the tip's triangle
	missileBody[2] = { tipPointX - width / 2, tipPointY + height }; // left point of the base
	missileBody[3] = { tipPointX + width / 2, tipPointY + height }; // right point of the base
	missileBody[4] = { tipPointX + width / 2, tipPointY + tipHeight }; // right point of the tip's triangle
}




void Missile::rotate(const float angle)
{

	center = { 0,0 };
	// Calculate the center of the missile's body by averaging the points
	for (int i = 0; i < 5; i++)
	{
		center.x += missileBody[i].x;
		center.y += missileBody[i].y;
	}

	center.x /= 5.0f;
	center.y /= 5.0f;
	
	
	// here we use radians directly in the sin and cos functions
	// radians to degrees: degrees = radians * (180 / PI)
	float s = sin(angle);
	float c = cos(angle);

	for (int i = 0; i < 5; i++)
	{
		/* We calculate the relative point to the origin (0,0) because rotation is around the center
		and each point is now relative to the center. We rotate only around the origin (0,0) in 2D space
		because the formula assumes the origin point is (0,0) so the center becomes (0,0) after the translation.
		The formula of rotation in 2D space is:
			x' = cos(a) * x - sin(a) * y
			y' = sin(a) * x + cos(a) * y
		*/

		// translate the point to be relative to origin (0,0) (the center basiclly becomes the origin (0,0))
		missileBody[i].x -= center.x;
		missileBody[i].y -= center.y;

		// rotate the point according to the formula above
		float newX = missileBody[i].x * c - missileBody[i].y * s;
		float newY = missileBody[i].x * s + missileBody[i].y * c;

		// translate point back to the original location by adding the center back
		missileBody[i].x = newX + center.x;
		missileBody[i].y = newY + center.y;
	}
}





