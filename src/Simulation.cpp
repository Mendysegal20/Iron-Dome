#include "Simulation.h"




Simulation::Simulation()
	: bgTexture{ 0 }, deltaTime(0.0f), launchEnemyTimer(0.0f) { }




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

	//SetConfigFlags(FLAG_VSYNC_HINT);
	//InitWindow(constants::screenWidth, constants::screenHeight, "Iron Dome Simulation");
	//
	//
	//int currentMonitor = GetCurrentMonitor();
	//screenWidth = GetMonitorWidth(currentMonitor);
	//screenHeight = static_cast<int>(GetMonitorHeight(currentMonitor) * 0.92f);

	////SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	////InitWindow(userScreenWidth, userScreenHeight, "Iron Dome Simulation");
	//
	//SetWindowSize(screenWidth, screenHeight);
	//SetWindowPosition(
	//	(GetMonitorWidth(currentMonitor) - screenWidth) / 2,
	//	(GetMonitorHeight(currentMonitor) - screenHeight) / 2
	//);

	//SetTargetFPS(60);
	
	WindowManager::init();


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

	Rectangle sourceRec = { 0.0f, 0.0f, (float)bgTexture.width, (float)bgTexture.height };

	// מותחים את התמונה ישירות מתחילת המסך (0,0) ועד לקצה הרוחב והגובה שלו
	Rectangle destRec = { 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() };

	while (!WindowShouldClose())
	{
		deltaTime = GetFrameTime();

		BeginDrawing();

			ClearBackground(RAYWHITE);
			//DrawTexture(bgTexture, 0, 0, WHITE);
			DrawTexturePro(bgTexture, sourceRec, destRec, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);
			
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

		else if(engagement.enemy.getState() == EnemyState::OnGround)
		{
			SoundManager::playExplosionSound();
			explosions.emplace_back(
				Explosion(engagement.enemy.getHitLine().lineEnd)
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
				 engagement.enemy.getState() == OnGround ||
				(engagement.enemy.getHitLine().lineStart.x < 0 || /*-constants::screenWidth ||*/
					engagement.enemy.getHitLine().lineStart.y > WindowManager::getWindowData().screenHeight /*constants::screenHeight*/);
		});
}





void Simulation::generateRockets(const float dt)
{
	if (launchEnemyTimer >= 0.06f)
	{
		launchEnemyTimer = 0.0f;
		
		
		const float enemyPosX = 1550.0f;
		const float enemyPosY = static_cast<float>(GetRandomValue(0, 250));

		const float enemySpeedX = static_cast<float>(GetRandomValue(300, 400));
		const float enemySpeedY = static_cast<float>(GetRandomValue(0, 300));
		
		EnemyRocket enemy(Vector2{ enemyPosX, enemyPosY},
						  Vector2{ enemySpeedX, enemySpeedY });

		Interceptor interceptor(Vector2{ WindowManager::getWindowData().batteryPositionX,
									     WindowManager::getWindowData().batteryPositionY },
								Vector2{ enemySpeedX * 2.5f, enemySpeedY * 2.5f });


		rockets.emplace_back(Engagement(interceptor, enemy));


		std::cout << "rockets size: " << rockets.size() << "\n";
		std::cout << "explosion size: " << explosions.size() << "\n";
	}
	else
		launchEnemyTimer += dt;
}
