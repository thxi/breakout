#include <stdio.h>

#include "raylib.h"

typedef struct Brick {
  Rectangle rect;
  // int alive;
  Color color;
} Brick;

int main(void) {
  const int screenWidth = 600;
  const int screenHeight = 400;

  InitWindow(screenWidth, screenHeight, "Breakout");

  Rectangle paddle = {
      .x = screenWidth / 2, .y = 380, .width = 40, .height = 10};

  const int nLines = 6;
  Color lineToColor[nLines] = {RED, ORANGE, GOLD, YELLOW, GREEN, BLUE};

  float brickWidth = 20;
  const int nBricks = screenWidth / brickWidth;
  printf("nbricks %d\n", nBricks);
  Brick bricks[nLines][nBricks];

  for (int line = 0; line < nLines; line++) {
    for (int i = 0; i < nBricks; i++) {
      bricks[line][i] = (Brick){{.x = i * brickWidth,
                                 .y = 50 + 10 * line,
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
    if (IsKeyDown(KEY_RIGHT)) paddle.x += 2.0f;
    if (IsKeyDown(KEY_LEFT)) paddle.x -= 2.0f;

    // Draw
    BeginDrawing();

    ClearBackground(RAYWHITE);

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