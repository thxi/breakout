#include "game.h"

void update_paddle(Rectangle* paddle, float deltaTime) {
  if (IsKeyDown(KEY_RIGHT)) paddle->x += 200 * deltaTime;
  if (IsKeyDown(KEY_LEFT)) paddle->x -= 200 * deltaTime;
}

void update_ball(Ball* ball, Rectangle paddle, float deltaTime) {
  ball->pos.x += ball->speed.x * deltaTime;
  ball->pos.y += ball->speed.y * deltaTime;
  collision_ball_wall(ball);
  collision_ball_paddle(ball, paddle);
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
bool collision_ball_paddle(Ball* ball, Rectangle paddle) {
  if (ball->pos.x + ball->radius >= paddle.x &&
      ball->pos.x - ball->radius <= paddle.x + paddle.width) {
    ball->color = BLUE;
    if (ball->pos.y + ball->radius >= paddle.y) {
      ball->speed.y *= -1;
    }
  } else {
    ball->color = GREEN;
  }
  return true;
}

bool collision_ball_bricks(Brick** bricks) {
  int nBricks = screenWidth / brickWidth;
  for (int line = 0; line < nLines; line++) {
    for (int i = 0; i < nBricks; i++) {
      Brick brick = bricks[line][i];
      if (brick.alive) {
      }
    }
  };
  return true;
}