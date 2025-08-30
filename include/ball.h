#ifndef BALL_H_
#define BALL_H_
#include <stdint.h>
#include <stdio.h>
#include "vector.h"

typedef struct {
  Vector position;
  Vector vel;
  float acceleration;

} Ball;

void ball_init(Ball *ball);
void ball_movement(Ball *ball);

#endif
