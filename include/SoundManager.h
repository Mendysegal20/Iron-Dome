#pragma once
#include <vector>
#include "raylib.h"
#include "Constants.h"


//struct SoundEffect
//{
//    SoundEffect(const char* soundPath)
//    {
//        sound = LoadSound(soundPath);
//	}
//
//    Sound sound;
//    bool isPlayed = false;
//};


class SoundManager
{
public:
    
    static void init();
    static void unloadAudio();
    
    static void playLaunchSound();
	static void playExplosionSound();
	//static void playSounds();
    

private:

	static Wave launchWave;
	static Wave explosionWave;
    static std::vector<Sound> launchPool;
	static std::vector<Sound> explosionPool;
    //static void update();
    
	
};

