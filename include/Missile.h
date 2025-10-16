#pragma once
#include <raylib.h>
#include <math.h>


class Missile
{

public:

	Missile(const Vector2& position, const Vector2& direction, const Vector2& velocity,
		const float width, const float height);
	
	virtual ~Missile() = default;
	
	virtual void draw() const = 0;
	virtual void update(const float dt);

	

protected:

	virtual void applyForces(const float dt) = 0;
	//void loadAssets(Texture2D& texture, const char* texturePath);
	void rotateHitLine();

	float angle;
	Vector2 spriteSize;
	Vector2 position;
	Vector2 velocity;
	Vector2 direction;
	Vector2 center;
	
	struct Line
	{
		Vector2 lineStart;
		Vector2 lineEnd;
	};
	
	Line hitLine;
};





