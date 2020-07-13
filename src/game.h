#pragma once

#include "raylib.h"

#define nLines 6
#define screenWidth 600
#define screenHeight 400

#define brickWidth 20
#define brickHeight 10
#define brickYOffset 50

#define paddleY 380

typedef struct Brick {
  Rectangle rect;
  bool alive;
  Color color;
} Brick;

typedef struct Ball {
  Vector2 pos;
  Vector2 speed;
  float radius;
  Color color;
} Ball;

void update_paddle(Rectangle* paddle, float deltaTime);
void update_ball(Ball* ball, Rectangle paddle, Brick* bricks, float deltaTime);
bool collision_ball_paddle(Ball* ball, Rectangle paddle);
bool collision_ball_wall(Ball* ball);
bool collision_ball_bricks(Ball* ball, Brick* bricks, float deltaTime);
bool collision_ball_brick(Ball* ball, Brick* brick, float deltaTime);