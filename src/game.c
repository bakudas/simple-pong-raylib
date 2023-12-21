#include "raylib.h"

#define PADDLE_SIZE 10
#define PADDLE_HEIGHT 100

struct paddle_t {
  Vector2 position;
  Vector2 size;
  Color color;
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
    paddle1.color = WHITE;
    
    // paddle 2
    Paddle paddle2;
    paddle2.position.x = (float)screenWidth - PADDLE_SIZE*2;
    paddle2.position.y = (float)screenHeight/2 - PADDLE_HEIGHT/2;
    paddle2.size.x = PADDLE_SIZE;
    paddle2.size.y = PADDLE_HEIGHT;
    paddle2.color = WHITE;

    // ball
    Paddle ball;
    int speed = 2;
    ball.position.x = (float)screenWidth/2;
    ball.position.y = (float)screenHeight/2;
    ball.size.x = 10;
    ball.size.y = 10;
    ball.color = WHITE;
        SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Controls
        if (IsKeyDown(KEY_UP)) paddle1.position.y -= paddle1.position.y >= 0 ? 2.0f : 0.0f;
        if (IsKeyDown(KEY_DOWN)) paddle1.position.y += paddle1.position.y <= (float)screenHeight - PADDLE_HEIGHT ? 2.0f : 0.0f;
        
        // Set paddle 1 collision
        Rectangle paddleCollision = { paddle1.position.x, paddle1.position.y, paddle1.size.x, paddle1.size.y };
        
        // Set paddle 2 collistion
        Rectangle paddleCollision2 = { paddle2.position.x, paddle2.position.y, paddle2.size.x, paddle2.size.y };

        // Set ball collision
        Rectangle ballCollision = { ball.position.x, ball.position.y, ball.size.x, ball.size.y };
    
        // Update ball velocity
        ball.position.x -= speed;
        
        // Set ball velocity
        if (CheckCollisionRecs(paddleCollision, ballCollision)) {
          speed = -2;
        }

        if (CheckCollisionRecs(paddleCollision2, ballCollision)){
          speed = 2;
        }
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
           
            // Draw middle line
            DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, WHITE);

            // Draw the paddle 1
            DrawRectangleV(paddle1.position, paddle1.size, paddle1.color);
            // Draw paddle 1 collision
            DrawRectangleLinesEx(paddleCollision, 1, GREEN);
  
            // Draw the paddle 2
            DrawRectangleV(paddle2.position, paddle2.size, paddle2.color);
            // Draw paddle 2 collision
            DrawRectangleLinesEx(paddleCollision2, 1, GREEN);

            // Draw the ball
            DrawRectangleV(ball.position, ball.size, ball.color);
            // Draw ball collision
            DrawRectangleLinesEx(ballCollision, 1, GREEN);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
