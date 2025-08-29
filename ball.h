#include <cstdint>
#include <ncurses.h>
#include <stdio.h>

#define MAX_SPEED = 2

typedef struct {
  float x;
  float y;

} Vector;

typedef struct {
  Vector x;
  Vector y;

  Vector vel_x;
  Vector vel_y;
  int aceleration;

} Ball;

void ball_movement(Ball *ball);
void ball_collision(Ball *ball);
