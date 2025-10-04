#pragma once
#include "Missile.h"


class Interceptor : public Missile
{

public:

	Interceptor(const Vector2& position, const Vector2& velocity);
	~Interceptor();
	
	void update(const float dt) override;
	void chase(const Line& targetPos, const float dt);
	void draw() const override;
	void checkForCollition(const Line& enemy);
	

private:

	void applyForces(const float dt) override;
	float boost;
	bool isEnemyClose;
	static Texture2D interceptorTexture;
};






