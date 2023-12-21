#include "raylib.h"
#include "raymath.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480
#define PADDLE_SIZE 10
#define PADDLE_HEIGHT 100
#define PADDLE_SPEED 150
#define BALL_SPEED 200

enum GameScreen {
  TITLE = 0,
  GAMEPLAY,
  ENDING
} typedef GameScreen;

struct paddle_t {
  Vector2 position;
  Vector2 size;
  int speed;
  Color color;
} typedef Paddle;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "c-game-engine @ vacaroxa");

    GameScreen currentScreen = TITLE;

    // core gameplay
    int scoreP1 = 0;
    int scoreP2 = 0;

    // paddle 1
    Paddle paddle1;
    paddle1.speed = 0;
    paddle1.position = (Vector2){ 10, (float)SCREEN_HEIGHT/2 - PADDLE_HEIGHT/2 };
    paddle1.size = (Vector2){ PADDLE_SIZE, PADDLE_HEIGHT };
    paddle1.color = WHITE;
    
    // paddle 2
    Paddle paddle2;
    paddle2.speed = 2;
    paddle2.position = (Vector2){ (float)SCREEN_WIDTH - PADDLE_SIZE*2, (float)SCREEN_HEIGHT/2 - PADDLE_HEIGHT/2 };
    paddle2.size = (Vector2){ PADDLE_SIZE, PADDLE_HEIGHT };
    paddle2.color = WHITE;

    // ball
    Paddle ball;
    int ballHorizontalSpeed = 2;
    int ballVerticalSpeed = 0;
    ball.position = (Vector2){ (float)SCREEN_WIDTH/2, (float)SCREEN_HEIGHT/2 };
    ball.size = (Vector2){ 10, 10 };
    ball.color = WHITE;
    
    // Collisions
    // Set paddle 1 collision
    Rectangle paddleCollision = (Rectangle){ paddle1.position.x, paddle1.position.y, paddle1.size.x, paddle1.size.y };
    
    // Set paddle 2 collistion
    Rectangle paddleCollision2 = (Rectangle){ paddle2.position.x, paddle2.position.y, paddle2.size.x, paddle2.size.y };

    // Set ball collision
    Rectangle ballCollision = (Rectangle){ ball.position.x, ball.position.y, ball.size.x, ball.size.y };


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Controls
        switch(currentScreen)
        {
          case TITLE:
            {
              if (IsKeyPressed(KEY_ENTER)) 
              {
                currentScreen = GAMEPLAY;
              }
            }
          case GAMEPLAY:
            {
              paddle1.speed = 0;

              if (IsKeyDown(KEY_UP)){
                paddle1.speed = -PADDLE_SPEED;
                paddle1.position.y += paddle1.position.y >= 0 ? paddle1.speed * GetFrameTime() : 0.0f;
              } 

              if (IsKeyDown(KEY_DOWN)) { 
                paddle1.speed = PADDLE_SPEED;
                paddle1.position.y += paddle1.position.y <= (float)SCREEN_HEIGHT - PADDLE_HEIGHT ? paddle1.speed * GetFrameTime() : 0.0f;
              }

              // Collisions
              // Set paddle 1 collision
              paddleCollision = (Rectangle){ paddle1.position.x, paddle1.position.y, paddle1.size.x, paddle1.size.y };
              
              // Set paddle 2 collistion
              paddleCollision2 = (Rectangle){ paddle2.position.x, paddle2.position.y, paddle2.size.x, paddle2.size.y };

              // Set ball collision
              ballCollision = (Rectangle){ ball.position.x, ball.position.y, ball.size.x, ball.size.y };
          
              // Ball 
              // Update ball velocity
              ball.position.x -= ballHorizontalSpeed;
              ball.position.y += ballVerticalSpeed;

              // Set ball velocity
              if (CheckCollisionRecs(paddleCollision, ballCollision)) {
                ballHorizontalSpeed = -BALL_SPEED * GetFrameTime();
                ballVerticalSpeed = paddle1.speed * GetFrameTime();
              }

              if (CheckCollisionRecs(paddleCollision2, ballCollision)){
                ballHorizontalSpeed = BALL_SPEED * GetFrameTime();
                //ballVerticalSpeed = paddle1.speed;
              }
              
              if (ball.position.y <= 0) ballVerticalSpeed *= -1;
              if (ball.position.y >= SCREEN_HEIGHT - ball.size.x) ballVerticalSpeed *= -1;
              
              // Scoring
              if (ball.position.x < 0) {
                scoreP2 += 1;
                ball.position.x = SCREEN_WIDTH/2 - ball.size.x;
                ball.position.y = SCREEN_HEIGHT/2 - ball.size.y;
              }

              if (ball.position.x > SCREEN_WIDTH + ball.size.x) {
                scoreP1 += 1;
                ball.position.x = SCREEN_WIDTH/2 - ball.size.x;
                ball.position.y = SCREEN_HEIGHT/2 - ball.size.y;
              }

              // Raytracing paddle 2
              if (ball.position.x > SCREEN_WIDTH/2) {
                paddle2.position.y = Lerp(paddle2.position.y, ball.position.y, 1.0f * GetFrameTime());
              } else {
                paddle2.position.y = Lerp(paddle2.position.y, SCREEN_HEIGHT/2 - paddle2.size.y, 1.0f * GetFrameTime());
              }   
            }
           
        }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
           
            switch(currentScreen)
            {
              case TITLE:
                {
                  DrawText(TextFormat("Press ENTER para iniciar o jogo.."), SCREEN_WIDTH/2 - 200, 200, 21, WHITE);
                } break;
              case GAMEPLAY:
                {
                  // Draw Score text
                  DrawText(TextFormat("%d", scoreP1), 30, 30, 42, WHITE);
                  DrawText(TextFormat("%d", scoreP2), SCREEN_WIDTH - 60, 30, 42, WHITE);

                  // Draw middle line
                  DrawLine(SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT, WHITE);

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

                } break;
            }
            
            EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
