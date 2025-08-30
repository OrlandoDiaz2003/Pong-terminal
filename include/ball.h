#ifndef BALL_H_
#define BALL_H_
#include <cstdint>
#include <stdio.h>
#include "vector.h"

typedef struct {
  Vector position;
  Vector vel;
  float aceleration;

} Ball;

void ball_init(Ball *ball);
void ball_movement(Ball *ball);

#endif
