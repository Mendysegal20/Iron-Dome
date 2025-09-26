#include <iostream>
#include <raylib.h>
//#include "box2d/box2d.h"
#include "Missile.h"
#include "EnemyRocket.h"
#define PI 3.14159265359


int main()
{
	
	InitWindow(1500, 867, "Iron Dome Simulation");
	SetTargetFPS(60);
	float deltaTime = 0;


	const char bg[20] = "assets/bg1.png";
	const char i[25] = "assets/interceptor2.png";
	const char r[20] = "assets/missile3.png";

	Image image = LoadImage(bg);
	Image inter = LoadImage(i);
	Image rocket = LoadImage(r);
	

	Texture2D texture = LoadTextureFromImage(image);
	Texture2D interceptor = LoadTextureFromImage(inter);
	Texture2D rocketTexture = LoadTextureFromImage(rocket);
	

	UnloadImage(image);
	UnloadImage(inter);
	UnloadImage(rocket);
	
	

	//EnemyRocket missile({ 1450, 50 }, { 100, 0 });
	//missile.rotate(0.001f);
	//EnemyRocket missile({ 1400, 100 }, { 0.5f, 0.0f });
	//missile.rotate(-0.5 * PI);


	Vector2 rocketPos = { 690, 700 };
	Vector2 interceptorPos = { 610, 710 };

	Rectangle rocketRect = { rocketPos.x, rocketPos.y, (float)rocketTexture.width, (float)rocketTexture.height };
	Rectangle interceptorRect = { interceptorPos.x, interceptorPos.y, (float)interceptor.width, (float)interceptor.height };

	float angle = 0.5f;

	
	while (!WindowShouldClose())    // לולאת המשחק
	{

		deltaTime = GetFrameTime();
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawTexture(texture, 0, 0, WHITE); // ציור הרקע



		//DrawTriangleFan(missile.missileBody, 5, BLACK);


		// ציור
		//angle += 0.6f;

		DrawTextureEx(rocketTexture, rocketPos, 0.0f, 1.0f, WHITE);
		DrawTextureEx(interceptor, interceptorPos, angle, 1.0f, WHITE);

		// הגדרת מלבני הקוליז'ן לפי מיקום + גודל הטקסטורה

		//DrawRectangleLinesEx(rocketRect, 3, RED);

		// בדיקת התנגשות
		if (CheckCollisionRecs(interceptorRect, rocketRect)) {
			DrawText("Collision!", 100, 100, 30, RED);
			//missile.update(deltaTime);
			//missile.rotate(0.1f);
		}

		EndDrawing();
	}
}
