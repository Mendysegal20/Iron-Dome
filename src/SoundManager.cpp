#include "SoundManager.h"
#include <iostream>



Wave SoundManager::launchWave = {};
Wave SoundManager::explosionWave = {};
std::vector<Sound> SoundManager::launchPool = {};
std::vector<Sound> SoundManager::explosionPool = {};


void SoundManager::init()
{
    InitAudioDevice();
	launchWave = LoadWave(constants::launchSoundPath);
	explosionWave = LoadWave(constants::explosionSoundPath);

	for(int i = 0; i < 4; i++)
	{
		Sound launchSound = LoadSoundFromWave(launchWave);
		Sound explosionSound = LoadSound(constants::explosionSoundPath);
		
		launchPool.emplace_back(launchSound);
		explosionPool.emplace_back(explosionSound);
	}
}






void SoundManager::unloadAudio()
{
	UnloadWave(launchWave);

	for (auto& sound : launchPool)
		UnloadSound(sound);

	for( auto& sound : explosionPool)
		UnloadSound(sound);

	launchPool.clear();
	explosionPool.clear();
	CloseAudioDevice();
}





void SoundManager::playLaunchSound()
{
	for (auto& sound : launchPool)
	{
		if (!IsSoundPlaying(sound))
		{
			PlaySound(sound);
			return;
		}
	}
}




void SoundManager::playExplosionSound()
{
	for (auto& sound : explosionPool)
	{
		if (!IsSoundPlaying(sound))
		{
			PlaySound(sound);
			return;
		}
	}
}



//void SoundManager::playSounds()
//{
//    for (auto& soundEffect : soundEffects)
//    {
//        if (!soundEffect.isPlayed)
//        {
//            PlaySound(soundEffect.sound);
//            soundEffect.isPlayed = true;
//        }
//    }
//
//    removePlayedSounds();
//}





//void SoundManager::addLaunchSound()
//{
//	Sound launchSound = LoadSound(constants::launchSoundPath);
//	soundEffects.emplace_back(SoundEffect(launchSound));
//	playSounds();
//}





//void SoundManager::update()
//{
//
//	std::erase_if(sounds, [](const Sound& sound)
//		{
//			if (!IsSoundPlaying(sound))
//			{
//				UnloadSound(sound);
//				return true;
//			}
//			
//			return false;
//		});
//
//	std::cout << "sounds size: " << sounds.size() << "\n";
//	
//}


