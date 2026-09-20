#pragma once
#include <raylib.h>
#include <optional>
#include "Constants.h"

struct WindowData
{
	const int screenWidth;
	const int screenHeight;

	const float batteryPositionX;
	const float batteryPositionY;
	const float ground;
	const Vector2 cityLeftBoundary;
	const Vector2 cityRightBoundary;

	WindowData(int width, int height)
		: screenWidth(width),
		  screenHeight(height),
		  batteryPositionX(width* constants::batteryXRatio),
		  batteryPositionY(height* constants::batteryYRatio),
		  ground(height * constants::groundRatio),
		  cityLeftBoundary({ width * constants::cityLeftBoundaryRatioX, 
			  height * constants::cityLeftBoundaryRatioY }),
		  cityRightBoundary({ width * constants::cityRightBoundaryRatioX, 
			  height * constants::cityRightBoundaryRatioY }) {}
};


class WindowManager
{
public:

	static const WindowData& getWindowData();
	static void init();


private:
	static inline std::optional<WindowData> windowData = std::nullopt;
};