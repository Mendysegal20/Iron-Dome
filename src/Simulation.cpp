#include "Simulation.h"




Simulation::Simulation()
	: deltaTime(0.0f), launchEnemyTimer(0.0f) { }




Simulation::~Simulation()
{
	rockets.clear();
	explosions.clear();
	AssetsManager::unloadAssets();
}






void Simulation::init()
{	
	WindowManager::init();
	AssetsManager::init();
}






void Simulation::run()
{

	Rectangle sourceRec = { 0.0f, 0.0f, (float)AssetsManager::getBackgroundImage().width, 
		(float)AssetsManager::getBackgroundImage().height };

	// מותחים את התמונה ישירות מתחילת המסך (0,0) ועד לקצה הרוחב והגובה שלו
	Rectangle destRec = { 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() };

	while (!WindowShouldClose())
	{
		deltaTime = GetFrameTime();

		BeginDrawing();

			ClearBackground(RAYWHITE);
			//DrawTexture(bgTexture, 0, 0, WHITE);
			DrawTexturePro(AssetsManager::getBackgroundImage(), sourceRec, destRec, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);
			
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
	if (launchEnemyTimer >= 0.8f)
	{
		launchEnemyTimer = 0.0f;
		
		
		const float enemyPosX = WindowManager::getWindowData().screenWidth + 50.0f;
		const float enemyPosY = static_cast<float>(GetRandomValue(0, 450));

		const float enemySpeedX = static_cast<float>(GetRandomValue(350, 450));
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
