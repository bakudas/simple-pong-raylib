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

    // core gameplay
    int scoreP1 = 0;
    int scoreP2 = 0;

    // paddle 1
    Paddle paddle1;
    int paddleSpeed = 0;
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
    int ballHorizontalSpeed = 2;
    int ballVerticalSpeed = 0;
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

        paddleSpeed = 0;

        if (IsKeyDown(KEY_UP)){
          paddleSpeed = -2;
          paddle1.position.y += paddle1.position.y >= 0 ? paddleSpeed : 0.0f;
        } 

        if (IsKeyDown(KEY_DOWN)) { 
          paddleSpeed = 2;
          paddle1.position.y += paddle1.position.y <= (float)screenHeight - PADDLE_HEIGHT ? paddleSpeed : 0.0f;
        }

        // Set paddle 1 collision
        Rectangle paddleCollision = { paddle1.position.x, paddle1.position.y, paddle1.size.x, paddle1.size.y };
        
        // Set paddle 2 collistion
        Rectangle paddleCollision2 = { paddle2.position.x, paddle2.position.y, paddle2.size.x, paddle2.size.y };

        // Set ball collision
        Rectangle ballCollision = { ball.position.x, ball.position.y, ball.size.x, ball.size.y };
    
        // Update ball velocity
        ball.position.x -= ballHorizontalSpeed;
        ball.position.y += ballVerticalSpeed;

        // Set ball velocity
        if (CheckCollisionRecs(paddleCollision, ballCollision)) {
          ballHorizontalSpeed = -2;
          ballVerticalSpeed = paddleSpeed;
        }

        if (CheckCollisionRecs(paddleCollision2, ballCollision)){
          ballHorizontalSpeed = 2;
          //ballVerticalSpeed = paddleSpeed;
        }
        
        if (ball.position.y <= 0) ballVerticalSpeed *= -1;
        if (ball.position.y >= screenHeight - ball.size.x) ballVerticalSpeed *= -1;

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
           
            // Draw Score text
            DrawText((char *)scoreP1, 30, 30, 42, WHITE);

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
