#pragma once
#include "Missile.h"


enum EnemyState {
	InFlight,
	OnGround
};


class EnemyRocket : public Missile
{

public:

	EnemyRocket(const Vector2& position, const Vector2& velocity);
	//~EnemyRocket();
	static void loadRocketTexture();
	static void unloadRocketTexture();
	void update(const float dt) override;
	void draw() const override;
	void checkIfOnGround();
	float getGravity() const;
	EnemyState getState() const;
	Vector2 getVelocity() const;

	
private:
	
	void applyForces(const float dt) override;
	float gravity;
	EnemyState state = InFlight;
	static Texture2D rocketTexture;
};






