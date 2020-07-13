#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

typedef struct Brick {
  Rectangle rect;
  // int alive;
  Color color;
} Brick;

typedef struct Ball {
  Vector2 pos;
  Vector2 speed;
  float radius;
  Color color;
} Ball;

void update_paddle(Rectangle* paddle, float deltaTime);
void update_ball(Ball* ball, float deltaTime);
bool collision_ball_paddle();
bool collision_ball_wall(Ball* ball);

int main(void) {
  const int screenWidth = 600;
  const int screenHeight = 400;

  InitWindow(screenWidth, screenHeight, "Breakout");

  const float paddleY = 380;
  Rectangle paddle = {
      .x = screenWidth / 2, .y = paddleY, .width = 40, .height = 10};

  const int nLines = 6;
  Color lineToColor[nLines] = {RED, ORANGE, GOLD, YELLOW, GREEN, BLUE};

  Ball ball = (Ball){
      .pos = {GetScreenWidth() / 2, GetScreenHeight() / 2},
      .speed = {200, 200},
      .radius = 5,
      .color = GREEN,
  };

  const float brickWidth = 20;
  const int nBricks = screenWidth / brickWidth;
  const float brickYOffset = 50;
  const float brickHeigh = 10;
  printf("nbricks %d\n", nBricks);
  Brick bricks[nLines][nBricks];

  for (int line = 0; line < nLines; line++) {
    for (int i = 0; i < nBricks; i++) {
      bricks[line][i] = (Brick){{.x = i * brickWidth,
                                 .y = brickYOffset + brickHeigh * line,
                                 .width = brickWidth,
                                 .height = 10},
                                .color = lineToColor[line]};
    }
  }
  printf("end init\n");
  SetTargetFPS(60);

  // Main game loop
  while (!WindowShouldClose())  // Detect window close button or ESC key
  {
    float deltaTime = GetFrameTime();

    update_paddle(&paddle, deltaTime);

    update_ball(&ball, deltaTime);
    printf("ball speed %f %f\n", ball.speed.x, ball.speed.y);

    // Draw
    BeginDrawing();
    DrawFPS(screenWidth - 90, screenHeight - 30);

    ClearBackground(RAYWHITE);
    DrawCircleV(ball.pos, ball.radius, ball.color);

    DrawText("move the paddle with arrow keys", 10, 10, 20, DARKGRAY);

    DrawRectangleRec(paddle, RED);

    for (int line = 0; line < nLines; line++) {
      for (int i = 0; i < nBricks; i++) {
        DrawRectangleRec(bricks[line][i].rect, bricks[line][i].color);
      }
    }

    EndDrawing();
  }

  // De-Initialization
  CloseWindow();  // Close window and OpenGL context

  return 0;
}

void update_paddle(Rectangle* paddle, float deltaTime) {
  if (IsKeyDown(KEY_RIGHT)) paddle->x += 200 * deltaTime;
  if (IsKeyDown(KEY_LEFT)) paddle->x -= 200 * deltaTime;
}

void update_ball(Ball* ball, float deltaTime) {
  ball->pos.x += ball->speed.x * deltaTime;
  ball->pos.y += ball->speed.y * deltaTime;
  collision_ball_wall(ball);
}

bool collision_ball_wall(Ball* ball) {
  if ((ball->pos.x >= (GetScreenWidth() - ball->radius)) ||
      (ball->pos.x <= ball->radius))
    ball->speed.x *= -1.0f;
  if ((ball->pos.y >= (GetScreenHeight() - ball->radius)) ||
      (ball->pos.y <= ball->radius))
    ball->speed.y *= -1.0f;
  return true;
}
bool collision_ball_paddle() { return true; }