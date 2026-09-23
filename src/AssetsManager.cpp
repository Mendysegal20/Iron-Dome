#include "AssetsManager.h"

Texture2D AssetsManager::bgTexture = { 0 };


//AssetsManager::AssetsManager()
//{
//}


void AssetsManager::init()
{
	Image image = LoadImage(constants::bgPath);
	bgTexture = LoadTextureFromImage(image);
	UnloadImage(image);

	SoundManager::init();
	EnemyRocket::loadRocketTexture();
	Interceptor::loadInterceptorTexture();
	Explosion::loadExplosionTexture();
}



AssetsManager::~AssetsManager()
{

	UnloadTexture(bgTexture);
	SoundManager::unloadAudio();
	EnemyRocket::unloadRocketTexture();
	Interceptor::unloadInterceptorTexture();
	Explosion::unloadExplosionTexture();
}



Texture2D const& AssetsManager::getBackgroundImage()
{
	return bgTexture;
}






