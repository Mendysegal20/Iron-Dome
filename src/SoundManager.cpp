#include "SoundManager.h"
//#include <iostream>
#define POOL_SIZE 5



Wave SoundManager::launchWave = {};
Wave SoundManager::explosionWave = {};
std::vector<Sound> SoundManager::launchPool = {};
std::vector<Sound> SoundManager::explosionPool = {};




void SoundManager::init()
{
    InitAudioDevice();
	launchWave = LoadWave(constants::launchSoundPath);
	explosionWave = LoadWave(constants::explosionSoundPath);

	for(int i = 0; i < POOL_SIZE; i++)
	{
		Sound launchSound = LoadSoundFromWave(launchWave);
		Sound explosionSound = LoadSound(constants::explosionSoundPath);
		
		launchPool.emplace_back(launchSound);
		explosionPool.emplace_back(explosionSound);
	}
}




void SoundManager::playSound(const std::vector<Sound>& sounds)
{
	for (const Sound& sound : sounds)
	{
		if (!IsSoundPlaying(sound))
		{
			PlaySound(sound);
			return;
		}
	}
}





void SoundManager::unloadAudio()
{
	UnloadWave(launchWave);
	UnloadWave(explosionWave);

	for (Sound& sound : launchPool)
		UnloadSound(sound);

	for( Sound& sound : explosionPool)
		UnloadSound(sound);

	launchPool.clear();
	explosionPool.clear();
	CloseAudioDevice();
}





void SoundManager::playLaunchSound()
{
	playSound(launchPool);
}




void SoundManager::playExplosionSound()
{	
	playSound(explosionPool);
}



