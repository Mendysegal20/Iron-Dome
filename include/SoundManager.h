#pragma once
#include "raylib.h"
#include "Constants.h"



class SoundManager
{

public:

	static void init();
	static void unloadAudio();

	static void playLaunchSound();
	static void playExplosionSound();
	static void playWarningSound();


private:

	static Sound launchSound;
	static bool isLaunchSoundPlayed;
};

