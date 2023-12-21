#include "raylib.h"

#define PADDLE_SIZE 10
#define PADDLE_HEIGHT 100

struct paddle_t {
  Vector2 position;
  Vector2 size;
} typedef Paddle;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "c-game-engine @ vacaroxa");

    // paddle 1
    Paddle paddle1;
    paddle1.position.x = 10;
    paddle1.position.y = (float)screenHeight/2 - PADDLE_HEIGHT/2;
    paddle1.size.x = PADDLE_SIZE;
    paddle1.size.y = PADDLE_HEIGHT;

    // paddle 2
    Paddle paddle2;
    paddle2.position.x = (float)screenWidth - PADDLE_SIZE*2;
    paddle2.position.y = (float)screenHeight/2 - PADDLE_HEIGHT/2;
    paddle2.size.x = PADDLE_SIZE;
    paddle2.size.y = PADDLE_HEIGHT;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        if (IsKeyDown(KEY_UP)) paddle1.position.y -= paddle1.position.y >= 0 ? 2.0f : 0.0f;
        if (IsKeyDown(KEY_DOWN)) paddle1.position.y += paddle1.position.y <= (float)screenHeight - PADDLE_HEIGHT ? 2.0f : 0.0f;


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            
            DrawLine(400, 0, 400, 450, WHITE);

            // Draw the paddle 1
            DrawRectangleV(paddle1.position, paddle1.size, WHITE);

            // Draw the paddle 2
            DrawRectangleV(paddle2.position, paddle2.size, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
