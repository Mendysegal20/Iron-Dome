#pragma once
#include "Missile.h"



class EnemyRocket : public Missile
{

public:

	EnemyRocket(const Vector2& position, const Vector2& velocity);
	~EnemyRocket();
	void update(const float dt);
	void draw() const override;
	
private:
	
	float gravity;
	static Texture2D rocketTexture;
};






