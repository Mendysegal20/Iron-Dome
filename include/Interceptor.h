#pragma once
#include "Missile.h"


class Interceptor : public Missile
{

public:

	Interceptor(const Vector2& position, const Vector2& velocity);
	~Interceptor();
	
	void update(const float dt);
	void draw() const override;
	

private:
	float boost;
	static Texture2D interceptorTexture;
};






