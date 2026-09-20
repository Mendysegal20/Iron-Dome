#pragma once


// may be put it in a json file later

namespace constants
{
	//inline constexpr int screenWidth = 1500;
	//inline constexpr int screenHeight = 867;

	inline constexpr float rocketWidth = 90.0f;
	inline constexpr float rocketHeight = 8.0f;

	inline constexpr float explosionTextureWidth = 96.0f;
	inline constexpr float explosionTextureHeight = 100.0f;

	inline constexpr float interceptorWidth = 70.0f;
	inline constexpr float interceptorHeight = 15.0f;

	//inline constexpr Vector2 batteryPosition = { 40.0f, 590.0f };
	inline constexpr float batteryXRatio = 0.0266f; // 40.0f / 1500
	inline constexpr float batteryYRatio = 0.6800f; // 590.0f / 867

	/*inline constexpr Vector2 cityRightBoundary = { 780.0f, 630.0f };*/
	inline constexpr float cityRightBoundaryRatioX = 0.52f; // 780.0f / 1500
	inline constexpr float cityRightBoundaryRatioY = 0.0333f; // 50.0f / 1500
	
	//inline constexpr Vector2 cityLeftBoundary = { 50.0f, 630.0f };
	inline constexpr float cityLeftBoundaryRatioX = 0.0333f; // 50.0f / 1500
	inline constexpr float cityLeftBoundaryRatioY = 0.7266f; // 630.0f / 867

	
	//inline constexpr float ground = 630.0f;
	inline constexpr float groundRatio = 0.7266; // 630.0f / 867

	inline constexpr char bgPath[30] = "assets/textures/bg1.png";
	inline constexpr char interceptorTexturePath[35] = "assets/textures/interceptor2.png";
	inline constexpr char rocketTexturePath[30] = "assets/textures/missile5.png";
	inline constexpr char explosionTexture[30] = "assets/textures/explosion.png";
	inline constexpr char explosionTexture2[35] = "assets/textures/explosion2.png";


	inline constexpr char launchSoundPath[25] = "assets/sounds/l5.wav";
	inline constexpr char launchSound2Path[25] = "assets/sounds/l4.wav";

	inline constexpr char explosionSoundPath[25] = "assets/sounds/exp2.wav";
}









