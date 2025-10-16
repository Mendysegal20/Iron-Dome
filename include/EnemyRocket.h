#pragma once
#include "Missile.h"



class EnemyRocket : public Missile
{

public:

	EnemyRocket(const Vector2& position, const Vector2& velocity);
	//~EnemyRocket();
	static void loadRocketTexture();
	static void unloadRocketTexture();
	//void update(const float dt);
	void draw() const override;
	float getGravity() const;
	Vector2 getVelocity() const;
	Line getHitLine() const;

	
private:
	
	void applyForces(const float dt) override;
	float gravity;
	static Texture2D rocketTexture;
};






