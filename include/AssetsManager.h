#pragma once
#include "Battery.h"
#include "EnemyRocket.h"
#include "Interceptor.h"
#include "Explosion.h"
#include "SoundManager.h"
#include "WindowManager.h"
#include <vector>
#include "Constants.h"


class AssetsManager
{

public:

	//AssetsManager(); // ctor
	~AssetsManager(); // dtor

	static void init();
	static const Texture2D& getBackgroundImage();

private:

	static Texture2D bgTexture;
};



