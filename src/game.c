#include "game.h"

#include <stdio.h>

void update_paddle(Rectangle* paddle, float deltaTime) {
  if (IsKeyDown(KEY_RIGHT)) paddle->x += 200 * deltaTime;
  if (IsKeyDown(KEY_LEFT)) paddle->x -= 200 * deltaTime;
}

void update_ball(Ball* ball, Rectangle paddle, Brick* bricks, float deltaTime) {
  ball->pos.x += ball->speed.x * deltaTime;
  ball->pos.y += ball->speed.y * deltaTime;
  collision_ball_wall(ball);
  collision_ball_paddle(ball, paddle);
  collision_ball_bricks(ball, bricks, deltaTime);
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
  // TODO
  // a bit incorrect
  // but fine for now
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

bool collision_ball_bricks(Ball* ball, Brick* bricks, float deltaTime) {
  int nBricks = screenWidth / brickWidth;
  // there is a way of speeding up this check by simply checking the bricks
  // whose x coordinate is close to ball's x coordinate
  for (int line = 0; line < nLines; line++) {
    for (int i = 0; i < nBricks; i++) {
      Brick* brick = bricks + (line * nBricks + i);
      if (brick->alive) {
        bool collision = collision_ball_brick(ball, brick, deltaTime);
        if (collision) {
          float ballx = ball->pos.x, bally = ball->pos.y;
          float prevx = ballx - ball->speed.x * deltaTime;
          float prevy = bally - ball->speed.y * deltaTime;
          float left = brick->rect.x;
          float right = brick->rect.x + brick->rect.width;
          float top = brick->rect.y;
          float bottom = brick->rect.y + brick->rect.height;
          printf("top %f, left %f, right %f, bottom %f\n", top, left, right,
                 bottom);
          printf("brick: %f %f\n", brick->rect.x, brick->rect.y);
          printf("prevx %f, prevy %f\n", prevx, prevy);
          printf("ball: %f %f\n", ball->pos.x, ball->pos.y);
          return true;
        }
      }
    }
  };
  return false;
}

bool collision_ball_brick(Ball* ball, Brick* brick, float deltaTime) {
  float ballx = ball->pos.x, bally = ball->pos.y;
  float prevx = ballx - ball->speed.x * deltaTime;
  float prevy = bally - ball->speed.y * deltaTime;

  float left = brick->rect.x;
  float right = brick->rect.x + brick->rect.width;
  float top = brick->rect.y;
  float bottom = brick->rect.y + brick->rect.height;

  // can be done in a switch case but who cares
  if (ballx >= left && ballx <= right) {
    if (prevy <= top && bally >= top) {
      // - top wall
      printf(" - top wall");
      ball->speed.y *= -1;
      goto collision;
    }
  }
  if (ballx >= left && ballx <= right) {
    if (prevy >= bottom && bally <= bottom) {
      // - bottom wall
      printf(" - bottom wall");
      ball->speed.y *= -1;
      goto collision;
    }
  }
  if (bally >= top && bally <= bottom) {
    if (prevx <= left && ballx >= left) {
      // | left wall
      printf(" | left wall");
      ball->speed.x *= -1;
      goto collision;
    }
  }
  if (bally >= top && bally <= bottom) {
    if (prevx >= right && ballx <= right) {
      // | right wall
      printf(" | right wall");
      ball->speed.x *= -1;
      goto collision;
    }
  }
  goto nocollision;
collision:
  brick->alive = false;
  brick->color = GRAY;
  ball->pos.x = prevx;
  ball->pos.y = prevy;
  return true;
nocollision:
  return false;
}