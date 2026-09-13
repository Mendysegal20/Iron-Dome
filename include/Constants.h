#pragma once


// may be put it in a json file later

namespace constants
{
	inline constexpr int screenWidth = 1500;
	inline constexpr int screenHeight = 867;

	inline constexpr float rocketWidth = 90.0f;
	inline constexpr float rocketHeight = 8.0f;

	inline constexpr float explosionTextureWidth = 96.0f;
	inline constexpr float explosionTextureHeight = 100.0f;

	inline constexpr float interceptorWidth = 70.0f;
	inline constexpr float interceptorHeight = 15.0f;

	//inline constexpr Vector2 batteryPosition = { 40.0f, 590.0f };
	inline constexpr float batteryXRatio = 0.0266f;
	inline constexpr float batteryYRatio = 0.6800f;

	inline constexpr Vector2 cityRightBoundary = { 780.0f, 630.0f };
	inline constexpr Vector2 cityLeftBoundary = { 50.0f, 630.0f };
	inline constexpr float ground = 630.0f;

	inline constexpr const char bgPath[30] = "assets/textures/bg1.png";
	inline constexpr const char interceptorTexturePath[35] = "assets/textures/interceptor2.png";
	inline constexpr const char rocketTexturePath[30] = "assets/textures/missile5.png";
	inline constexpr const char explosionTexture[30] = "assets/textures/explosion.png";
	inline constexpr const char explosionTexture2[35] = "assets/textures/explosion2.png";


	inline constexpr const char launchSoundPath[25] = "assets/sounds/l5.wav";
	inline constexpr const char launchSound2Path[25] = "assets/sounds/l4.wav";

	inline constexpr const char explosionSoundPath[25] = "assets/sounds/exp2.wav";
}









