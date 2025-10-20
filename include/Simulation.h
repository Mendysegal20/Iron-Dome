#pragma once
#include "Battery.h"
#include "EnemyRocket.h"
#include "Interceptor.h"
#include "Explosion.h"
#include "SoundManager.h"
#include <vector>


struct Engagement {
	
	Engagement() = default;
	Engagement(const Interceptor& inter, const EnemyRocket& enem)
		:interceptor(inter), enemy(enem) {}
	
	Interceptor interceptor;
	EnemyRocket enemy;
};




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
	
	//std::vector<std::pair<Interceptor, EnemyRocket>> rockets;
	std::vector<Engagement> rockets;
	std::vector<Explosion> explosions;
	Texture2D bgTexture;
	Battery battery;
	
	void generateRockets(const float dt);
	void update(const float dt);
	void updateExplosions(const float dt);
	void updateRockets(const float dt);
	void removeInactiveObjects();
	bool isThreat(const EnemyRocket& enemy);
	
};







