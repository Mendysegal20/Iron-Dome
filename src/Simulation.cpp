#include "Simulation.h"



Simulation::~Simulation()
{
	UnloadTexture(bgTexture);
	rockets.clear();
	explosions.clear();

	SoundManager::unloadAudio();
	EnemyRocket::unloadRocketTexture();
	Interceptor::unloadInterceptorTexture();
	Explosion::unloadExplosionTexture();
}








void Simulation::init()
{
	//SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1500, 867, "Iron Dome Simulation");
	SetTargetFPS(60);

	Image image = LoadImage(constants::bgPath);
	bgTexture = LoadTextureFromImage(image);
	UnloadImage(image);

	SoundManager::init();
	EnemyRocket::loadRocketTexture();
	Interceptor::loadInterceptorTexture();
	Explosion::loadExplosionTexture();
}






void Simulation::run()
{

	while (!WindowShouldClose())
	{
		deltaTime = GetFrameTime();

		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawTexture(bgTexture, 0, 0, WHITE);

		update(deltaTime);
		generateRockets(deltaTime);
		
		EndDrawing();
	}

	CloseWindow();
}







void Simulation::update(const float dt)
{
	updateRockets(dt);
	updateExplosions(dt);
	removeInactiveObjects();
}







void Simulation::updateRockets(const float dt)
{
	for (Engagement& engagement : rockets)
	{
		engagement.interceptor.update(engagement.enemy.getHitLine(), dt);
		engagement.interceptor.draw();

		engagement.enemy.update(dt);
		engagement.enemy.draw();

		battery.evaluateThreat(engagement.interceptor, engagement.enemy);

		if (engagement.interceptor.getState() == InterceptorState::HitTarget)
		{
			SoundManager::playExplosionSound();
			explosions.emplace_back(
				Explosion(engagement.interceptor.getHeadPosition())
			);
		}
			
	}
}





void Simulation::updateExplosions(const float dt)
{
	for (Explosion& explosion : explosions)
	{
		explosion.update(dt);
		explosion.draw();
	}
}







void Simulation::removeInactiveObjects()
{
	std::erase_if(explosions, [](const Explosion& explosion)
		{
			return !explosion.isActive();
		});



	std::erase_if(rockets, [](const Engagement& engagement)
		{
			return engagement.interceptor.getState() == HitTarget ||
				(engagement.enemy.getHitLine().lineStart.x < 0 || /*-constants::screenWidth ||*/
					engagement.enemy.getHitLine().lineStart.y > constants::screenHeight);
		});
}





void Simulation::generateRockets(const float dt)
{
	if (lanchEnemyTimer >= 1.5f)
	{
		lanchEnemyTimer = 0.0f;
		
		
		const float enemyPosX = 1550.0f;
		const float enemyPosY = static_cast<float>(GetRandomValue(0, 250));

		const float enemySpeedX = static_cast<float>(GetRandomValue(300, 400));
		const float enemySpeedY = static_cast<float>(GetRandomValue(0, 150));
		
		EnemyRocket enemy(Vector2{ enemyPosX, enemyPosY},
						  Vector2{ enemySpeedX, enemySpeedY });

		Interceptor interceptor(Vector2{ constants::batteryPosition.x,
									     constants::batteryPosition.y },
								Vector2{ enemySpeedX * 2.5f, enemySpeedY * 2.5f });


		rockets.emplace_back(Engagement(interceptor, enemy));


		std::cout << "rockets size: " << rockets.size() << "\n";
		std::cout << "explosion size: " << explosions.size() << "\n";
	}
	else
		lanchEnemyTimer += dt;
}





//bool Simulation::isThreat(const EnemyRocket& enemy)
//{
//	/*
//			the formula of motion under gravity is:
//			y(t) = y0 + vy * t + 0.5 * gt^2
//
//			y(t) means the height of the rocket at time t
//			y0 means the initial height of the rocket
//			vy means the vertical component of the rocket's velocity
//			g means the gravity
//		*/
//
//	float a = 0.5f * enemy.getGravity();
//	float b = enemy.getVelocity().y;
//	float c = enemy.getHitLine().lineEnd.y - constants::ground;
//	float discriminant = b * b - 4 * a * c;
//
//
//	if (discriminant < 0.0f)
//		return false; // No real solutions, the rocket will not hit the ground
//
//	float t1 = (-b + sqrtf(discriminant)) / (2 * a);
//	float t2 = (-b - sqrtf(discriminant)) / (2 * a);
//	float t = -1.0f;
//
//	if (t1 <= 0.0f && t2 <= 0.0f)
//		return false;
//
//	if (t1 > 0.0f && t2 > 0.0f)
//		t = std::min(t1, t2);
//
//	else
//		t = (t1 > 0.0f) ? t1 : t2;
//
//	if (t <= 0.0f)
//		return false; // Both solutions aren't positive, the rocket will not hit the ground
//
//
//	//float bufferTime = 0.3f;
//	float impactX = enemy.getHitLine().lineEnd.x + enemy.getVelocity().x * t; //(t * bufferTime);
//
//
//	if ((impactX < constants::cityRightBoundary.x
//		&& impactX > constants::cityLeftBoundary.x))
//		return true;
//
//	return false;
//}




