#include "SoundManager.h"



Sound SoundManager::launchSound = { 0 };
bool SoundManager::isLaunchSoundPlayed = false;



void SoundManager::init()
{
	InitAudioDevice();
	launchSound = LoadSound(constants::launchSoundPath);
	isLaunchSoundPlayed = false;
}




void SoundManager::unloadAudio()
{
	UnloadSound(launchSound);
	CloseAudioDevice();
}



void SoundManager::playLaunchSound()
{
	if (!isLaunchSoundPlayed)
	{
		PlaySound(launchSound);
		isLaunchSoundPlayed = true;
	}
}




void SoundManager::playExplosionSound()
{
	// Play explosion sound
}



void SoundManager::playWarningSound()
{
	// Play warning sound
}

















