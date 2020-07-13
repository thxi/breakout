#pragma once

#include "raylib.h"

#define nLines 6
#define screenWidth 600
#define screenHeight 400

#define brickWidth 20
#define brickHeight 30
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
void update_ball(Ball* ball, Rectangle paddle, float deltaTime);
bool collision_ball_paddle(Ball* ball, Rectangle paddle);
bool collision_ball_wall(Ball* ball);