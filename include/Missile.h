#pragma once
#include <raylib.h>
#include <math.h>


class Missile
{

public: 

	Missile(const Vector2& position, const Vector2& velocity, 
		const float width, const float height);
	
	void rotateHitLine();
	virtual void draw() const = 0;


protected:

	float angle;
	Vector2 spriteSize;
	Vector2 position;
	Vector2 velocity;
	Vector2 center;
	
	struct Line
	{
		Vector2 lineStart;
		Vector2 lineEnd;
	};

	Line hitLine;
};





