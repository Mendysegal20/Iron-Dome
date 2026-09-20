#include "WindowManager.h"



void WindowManager::init()
{
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(1500, 867, "Iron Dome Simulation");
	
	// Get and set the size of the window
	int currentMonitor = GetCurrentMonitor();
	int width = GetMonitorWidth(currentMonitor);
	int height = static_cast<int>(GetMonitorHeight(currentMonitor) * 0.92f);

	SetWindowSize(width, height);
	SetWindowPosition(
		(GetMonitorWidth(currentMonitor) - width) / 2,
		(GetMonitorHeight(currentMonitor) - height) / 2
	);

	// Create the WindowData object with the updated width and height
	windowData.emplace(width, height);
	SetTargetFPS(60);
}


const WindowData& WindowManager::getWindowData()
{
	return *windowData;
}









