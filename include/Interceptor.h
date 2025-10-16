#pragma once
#include "Missile.h"



enum InterceptorState {
	Idle,
	Launched
};



class Interceptor : public Missile
{

public:

	Interceptor(const Vector2& position, const Vector2& velocity);
	//~Interceptor();
	
	/*const Line* targetPosition = nullptr;*/
	InterceptorState state = Idle;

	void update(const float dt) override;
	void chase(const Line& targetPos, const float dt);
	void draw() const override;
	void checkForCollition(const Line& enemy);
	
	static void loadInterceptorTexture();
	static void unloadInterceptorTexture();
	
	

private:

	void applyForces(const float dt) override;
	float boost;
	static Texture2D interceptorTexture;
};






