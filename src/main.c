#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "raylib.h"

int main() {
  InitWindow(screenWidth, screenHeight, "Breakout");

  Rectangle paddle = {
      .x = screenWidth / 2, .y = paddleY, .width = 40, .height = 10};

  Color lineToColor[nLines] = {RED, ORANGE, GOLD, YELLOW, GREEN, BLUE};

  Ball ball = (Ball){
      .pos = {400, 350},
      .speed = {.x = 300, .y = -300},
      .radius = 5,
      .color = GREEN,
  };

  const int nBricks = screenWidth / brickWidth;

  printf("nbricks %d\n", nBricks);
  Brick bricks[nLines][nBricks];

  for (int line = 0; line < nLines; line++) {
    for (int i = 0; i < nBricks; i++) {
      bricks[line][i] = (Brick){{.x = i * brickWidth,
                                 .y = brickYOffset + brickHeight * line,
                                 .width = brickWidth,
                                 .height = brickHeight},
                                .alive = true,
                                .color = lineToColor[line]};
    }
  }

  SetTargetFPS(60);
  printf("end init\n");

  // Main game loop
  while (!WindowShouldClose())  // Detect window close button or ESC key
  {
    float deltaTime = GetFrameTime();

    update_paddle(&paddle, deltaTime);
    update_ball(&ball, paddle, (void*)bricks, deltaTime);

    // Draw
    BeginDrawing();
    DrawFPS(screenWidth - 90, screenHeight - 30);

    ClearBackground(RAYWHITE);

    DrawText("move the paddle with arrow keys", 10, 10, 20, DARKGRAY);

    DrawRectangleRec(paddle, RED);

    for (int line = 0; line < nLines; line++) {
      for (int i = 0; i < nBricks; i++) {
        if (bricks[line][i].alive) {
          DrawRectangleRec(bricks[line][i].rect, bricks[line][i].color);
          Brick b = bricks[line][i];
          DrawLine(b.rect.x, b.rect.y, b.rect.x, b.rect.y + b.rect.height,
                   BLACK);
        }
      }
    }

    DrawCircleV(ball.pos, ball.radius, ball.color);

    EndDrawing();
  }

  // De-Initialization
  CloseWindow();  // Close window and OpenGL context

  return 0;
}