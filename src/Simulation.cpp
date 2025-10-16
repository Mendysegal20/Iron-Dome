#include "Simulation.h"



Simulation::~Simulation()
{
	UnloadTexture(bgTexture);
	EnemyRocket::unloadRocketTexture();
	Interceptor::unloadInterceptorTexture();
}



void Simulation::init()
{
	//SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1500, 867, "Iron Dome Simulation");
	SetTargetFPS(60);

	Image image = LoadImage(constants::bgPath);
	bgTexture = LoadTextureFromImage(image);
	UnloadImage(image);

	EnemyRocket::loadRocketTexture();
	Interceptor::loadInterceptorTexture();
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
	
	
	for(auto& pair : rockets)
	{
		if (pair.first.state == Idle)
		{
			if(Battery::isThreat(pair.second))
				pair.first.state = Launched;
		}

		if (pair.first.state == Launched)
		{
			pair.first.update(dt);
			pair.first.draw();
			pair.first.chase(pair.second.getHitLine(), dt);
		}

		pair.second.update(dt);
		pair.second.draw();
	}
	
	

	std::erase_if(rockets, 
		[](const std::pair<Interceptor, EnemyRocket>& pair)
	{
		return pair.second.getHitLine().lineStart.x < 0 ||
			   pair.second.getHitLine().lineStart.y > constants::screenHeight;
	});
	
	
	//for (EnemyRocket& enemy : enemys)
	//{
	//	enemy.update(dt);
	//	enemy.draw();
	//}
	//
	////battery.update(dt);
	//
	//std::erase_if(enemys, [](const EnemyRocket& enemy)
	//{
	//	return enemy.getHitLine().lineStart.x < 0 ||
	//		   enemy.getHitLine().lineStart.y > constants::screenHeight;
	//});
}






void Simulation::generateRockets(const float dt)
{
	if (lanchEnemyTimer >= 2.0f)
	{
		lanchEnemyTimer = 0.0f;
		
		EnemyRocket enemy(Vector2{ 1550.0f, static_cast<float>(GetRandomValue(0, 250))},
						  Vector2{ static_cast<float>(GetRandomValue(300, 400)), 
								   static_cast<float>(GetRandomValue(0, 150)) });

		Interceptor interceptor(Vector2{ constants::batteryPosition.x,
									     constants::batteryPosition.y },
								Vector2{ 570.0f, 400.0f });


		rockets.push_back(std::make_pair(interceptor, enemy));



		//std::cout << rockets.size() << "The size of rockets vector\n";
		//enemys.push_back(enemy);
		/*rockets.push_back(std::make_pair(enemy, Interceptor(
			Vector2{ constants::batteryPosition.x, constants::batteryPosition.y },
			Vector2{ 470.0f, 300.0f })));*/

		//EnemyRocket& enemyRef = enemys.back();

		/*if(battery.isThreat(enemyRef))
			battery.lanchInterceptor(enemyRef, dt);*/
	}
	else
		lanchEnemyTimer += dt;
}




