#pragma once
#include "Missile.h"
#include "Explosion.h"



enum InterceptorState {
	Idle,
	Launched,
	HitTarget
};


class Interceptor : public Missile
{

public:

	Interceptor(const Vector2& position, const Vector2& velocity);

	void update(const Line& enemyPos, const float dt);
	//void update(const float dt) override;
	void chase(const Line& targetPos, const float dt);
	void draw() const override;
	void checkForCollition(const Line& enemy);
	Vector2 getHeadPosition() const;
	InterceptorState getState() const;
	void lunch();
	
	static void loadInterceptorTexture();
	static void unloadInterceptorTexture();
	

private:

	void applyForces(const float dt) override;
	float boost;
	InterceptorState state = Idle;
	static Texture2D interceptorTexture;
};






