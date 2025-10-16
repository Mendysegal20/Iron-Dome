#pragma once
#include "Battery.h"
#include "EnemyRocket.h"
#include "Interceptor.h"


class Simulation
{
public:
	
	Simulation() = default;
	~Simulation();
	
	void init();
	void run();

private:
	
	float deltaTime = 0.0f;
	float lanchEnemyTimer = 0.0f;
	//std::vector<std::pair<std::optional<Interceptor>, EnemyRocket>> rockets;
	
	std::vector<std::pair<Interceptor, EnemyRocket>> rockets;
	//std::vector <EnemyRocket> enemys;
	Texture2D bgTexture;
	//Battery battery;
	
	void generateRockets(const float dt);
	void update(const float dt);
	
};







