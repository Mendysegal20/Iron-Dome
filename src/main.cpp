#include <iostream>
#include <raylib.h>
//#include "box2d/box2d.h"
#include "Missile.h"


int main()
{
	
	InitWindow(1500, 867, "Iron Dome Simulation");
	SetTargetFPS(60);


	const char bg[20] = "assets/bg1.png";

	Image image = LoadImage(bg);
	Texture2D texture = LoadTextureFromImage(image);
	UnloadImage(image);

	Missile missile({ 55, 580 }, { 0, 0 });
	//missile.rotate(0.001f);


	while(!WindowShouldClose())    // לולאת המשחק
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawTexture(texture, 0, 0, WHITE); // ציור הרקע
		

		// ציור הטיל
		DrawTriangleFan(missile.missileBody, 5, BLACK);
		missile.rotate(0.1f);
		EndDrawing();
	}
}
