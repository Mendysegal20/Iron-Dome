#include <iostream>
#include <raylib.h>
#include "Missile.h"
#include "EnemyRocket.h"
#include "Interceptor.h"

//void moveSprite(Vector2& position)
//{
//    if (IsKeyDown(KEY_DOWN))
//        position.y += 1;
//    else if (IsKeyDown(KEY_UP))
//        position.y -= 1;
//    else if (IsKeyDown(KEY_RIGHT))
//        position.x += 1;
//    else if (IsKeyDown(KEY_LEFT))
//        position.x -= 1;
//}

// מחשב את מיקום המעגל בראש המיירט לפי הפינה השמאלית-עליונה
//void rotateCircle(Vector2& circlePos, const Vector2& spritePos, const Vector2& spriteSize, float angle)
//{
//    Vector2 offset = { spriteSize.x, spriteSize.y / 1.6f }; // מיקום המעגל יחסית לפינה
//    float rad = angle * DEG2RAD;
//    circlePos.x = spritePos.x + offset.x * cosf(rad) - offset.y * sinf(rad);
//    circlePos.y = spritePos.y + offset.x * sinf(rad) + offset.y * cosf(rad);
//}

//void rotateLine(Vector2& newStart, Vector2& newEnd, const Vector2& spritePos, const Vector2& spriteSize, float angle)
//{
//    /*
//        Rotate a line inside a sprite around the sprite's top-left corner.
//
//        Parameters:
//        - start, end: references to the line's start and end points (output)
//        - spritePos: the start position of the sprite wech is the top-left corner of the sprite
//        - spriteSize: width and height of the sprite
//        - angle: rotation angle in degrees
//
//        How it works:
//        1. Define the line's start and end points relative to the sprite's top-left corner.
//        2. Convert the rotation angle to radians.
//        3. Rotate each point around the origin (0,0) using the standard 2D rotation formula:
//              x' = cos(a) * x - sin(a) * y
//              y' = sin(a) * x + cos(a) * y
//               (here, x and y are offsets from the sprite's top-left corner
//                for example if the sprite position starts at (300,300) and the point we
//                want to rotate is at (400,400), then the ofsset to that point would be (100,100)
//                and we will calculate the point (100,100) with the formula and then we will add
//                the sprite's starts position (300,300) to have the point rotated according
//                to the origin (300,300) and not (0,0))
//        4. Add spritePos to convert the rotated points to absolute screen coordinates.
//    */
//    
//    
//    /* Calculate the start and the end points of the hit line.
//       start will be at (0.25 * width, 0.5 * height)
//       end will be at (width, 0.5 * height)*/
//    Vector2 oldStart = { spriteSize.x / 4.0f, spriteSize.y / 2.0f };
//    Vector2 oldEnd = { spriteSize.x, spriteSize.y / 2.0f };
//
//    float rad = angle * DEG2RAD;
//
//    
//    // Calculate accordding to the formula above
//    newStart.x = spritePos.x + oldStart.x * cosf(rad) - oldStart.y * sinf(rad);
//    newStart.y = spritePos.y + oldStart.x * sinf(rad) + oldStart.y * cosf(rad);
//
//    newEnd.x = spritePos.x + oldEnd.x * cosf(rad) - oldEnd.y * sinf(rad);
//    newEnd.y = spritePos.y + oldEnd.x * sinf(rad) + oldEnd.y * cosf(rad);
//}



int main()
{
    InitWindow(1500, 867, "Iron Dome Simulation");
    SetTargetFPS(60);

    Image image = LoadImage("assets/bg1.png");
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);

    float deltaTime;
    
    EnemyRocket enemy(Vector2{ 1500, 10 }, Vector2{ 390.0f, 0.0f });
    EnemyRocket enemy2(Vector2{ 1500, 50 }, Vector2{ 420.0f, 140.0f });
    Interceptor interceptor(Vector2{ 20, 630 }, Vector2{ 420.0f, 200.0f });

    while (!WindowShouldClose())
    {
        deltaTime = GetFrameTime();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(texture, 0, 0, WHITE);

        
        enemy.update(deltaTime);
        enemy2.update(deltaTime);
        interceptor.update(deltaTime);
        interceptor.chase(enemy2.getHitLine(), deltaTime);
        
        /*enemy.rotateHitLine();
        interceptor.rotateHitLine();
        enemy2.rotateHitLine();*/
        interceptor.checkForCollition(enemy2.getHitLine());
        

        
        enemy.draw();
        interceptor.draw();
        enemy2.draw();

        EndDrawing();
    }

    UnloadTexture(texture);

    CloseWindow();
}
