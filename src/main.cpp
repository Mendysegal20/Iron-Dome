#include <iostream>
#include <raylib.h>
#include "Missile.h"
#include "EnemyRocket.h"

void moveSprite(Vector2& position)
{
    if (IsKeyDown(KEY_DOWN))
        position.y += 1;
    else if (IsKeyDown(KEY_UP))
        position.y -= 1;
    else if (IsKeyDown(KEY_RIGHT))
        position.x += 1;
    else if (IsKeyDown(KEY_LEFT))
        position.x -= 1;
}

// מחשב את מיקום המעגל בראש המיירט לפי הפינה השמאלית-עליונה
void rotateCircle(Vector2& circlePos, const Vector2& spritePos, const Vector2& spriteSize, float angle)
{
    Vector2 offset = { spriteSize.x, spriteSize.y / 1.6f }; // מיקום המעגל יחסית לפינה
    float rad = angle * DEG2RAD;
    circlePos.x = spritePos.x + offset.x * cosf(rad) - offset.y * sinf(rad);
    circlePos.y = spritePos.y + offset.x * sinf(rad) + offset.y * cosf(rad);
}

// מחשב נקודות קו בתוך המיירט ומסובב ביחד איתו
void rotateLine(Vector2& newStart, Vector2& newEnd, const Vector2& spritePos, const Vector2& spriteSize, float angle)
{
    /*
        Rotate a line inside a sprite around the sprite's top-left corner.

        Parameters:
        - start, end: references to the line's start and end points (output)
        - spritePos: the start position of the sprite wech is the top-left corner of the sprite
        - spriteSize: width and height of the sprite
        - angle: rotation angle in degrees

        How it works:
        1. Define the line's start and end points relative to the sprite's top-left corner.
        2. Convert the rotation angle to radians.
        3. Rotate each point around the origin (0,0) using the standard 2D rotation formula:
              x' = cos(a) * x - sin(a) * y  
              y' = sin(a) * x + cos(a) * y  
           (here, x and y are offsets from the sprite's top-left corner)
        4. Add spritePos to convert the rotated points to absolute screen coordinates.
    */
    
    
    // Calculate the start and the end points of the hit line:
    // start will be at (0.25 * width, 0.5 * height)
    // end will be at (width, 0.5 * height)
    Vector2 oldStart = { spriteSize.x / 4.0f, spriteSize.y / 2.0f };
    Vector2 oldEnd = { spriteSize.x, spriteSize.y / 2.0f };

    float rad = angle * DEG2RAD;

    
    // Calculate accordding to the formula above
    newStart.x = spritePos.x + oldStart.x * cosf(rad) - oldStart.y * sinf(rad);
    newStart.y = spritePos.y + oldStart.x * sinf(rad) + oldStart.y * cosf(rad);

    newEnd.x = spritePos.x + oldEnd.x * cosf(rad) - oldEnd.y * sinf(rad);
    newEnd.y = spritePos.y + oldEnd.x * sinf(rad) + oldEnd.y * cosf(rad);
}

int main()
{
    InitWindow(1500, 867, "Iron Dome Simulation");
    SetTargetFPS(60);

    Image image = LoadImage("assets/bg1.png");
    Image inter = LoadImage("assets/interceptor2.png");
    Image rocket = LoadImage("assets/missile3.png");

    Texture2D texture = LoadTextureFromImage(image);
    Texture2D interceptorTexture = LoadTextureFromImage(inter);
    Texture2D rocketTexture = LoadTextureFromImage(rocket);

    UnloadImage(image);
    UnloadImage(inter);
    UnloadImage(rocket);

    Vector2 rocketPos = { 690, 700 };
    Vector2 interceptorPos = { 580, 690 };

    /*float raduisRocket = 5.0f;
    float radiusInterceptor = 5.0f;*/

    /*Vector2 rocketCenter;
    Vector2 interceptorHead;*/
    
    Vector2 lineStart, lineEnd;
    Vector2 rocketLineStart = rocketPos, 
        rocketLineEnd = {rocketPos.x, 
        rocketPos.y + (float)rocketTexture.height};

    float angle = 0.5f;
    float deltaTime;

    while (!WindowShouldClose())
    {
        deltaTime = GetFrameTime();

        // הזזת המיירט אם רוצים
        moveSprite(interceptorPos);

        // סיבוב המעגל בראש המיירט
        //rotateCircle(interceptorHead, interceptorPos, { (float)interceptorTexture.width, (float)interceptorTexture.height }, angle);

        // סיבוב הקו בתוך המיירט
        rotateLine(lineStart, lineEnd, interceptorPos, { (float)interceptorTexture.width, (float)interceptorTexture.height }, angle);

        // המעגל של הטיל נשאר קבוע
        //rocketCenter = { rocketPos.x + (float)rocketTexture.width - 5, rocketPos.y + (float)rocketTexture.height / 2.0f };

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(texture, 0, 0, WHITE);
        DrawTextureEx(rocketTexture, rocketPos, 0.0f, 1.0f, WHITE);
        DrawTextureEx(interceptorTexture, interceptorPos, angle, 1.0f, WHITE);

        //DrawCircle(rocketCenter.x, rocketCenter.y, raduisRocket, RED);
        //DrawCircle(interceptorHead.x, interceptorHead.y, radiusInterceptor, BLUE);

        DrawLineV(lineStart, lineEnd, RED); // הקו שמסתובב עם המיירט
        DrawLineV(rocketLineStart, rocketLineEnd, RED);


        /*if (CheckCollisionCircles(rocketCenter, raduisRocket, interceptorHead, radiusInterceptor))
            DrawText("Collision!", 100, 100, 30, RED);*/

        if(CheckCollisionLines(lineStart, lineEnd, rocketLineStart, rocketLineEnd, NULL))
            DrawText("Collision!", 400, 100, 30, BLUE);

        EndDrawing();

        angle += 0.6f;
    }

    UnloadTexture(interceptorTexture);
    UnloadTexture(texture);
    UnloadTexture(rocketTexture);

    CloseWindow();
}
