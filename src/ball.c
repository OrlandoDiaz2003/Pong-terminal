#include "../include/ball.h"
#include "../include/game.h"
#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>

void ball_init(Ball *ball) {
  ball->position.x = WIDTH / 2.0;
  ball->position.y = HEIGHT / 2.0;
  ball->vel.x = 0;
  ball->vel.y = 0;
  ball->acceleration = 2.0;
}

void ball_movement(Ball *ball) {
  // deleting the last draw of the ball
  mvaddch(ball->position.y, ball->position.x, ' ');

  ball->position.x += ball->vel.x;
  ball->position.y += ball->vel.y;

  bool collision_x = ball->position.x <= 0 || ball->position.x >= COLS - 1;
  bool collision_y = ball->position.y <= 0 || ball->position.y >= LINES - 1;

  if (collision_x) {
    ball->position.x = WIDTH / 2.0;
    ball->vel.x *= -1;
  }

  if (collision_y) {
    ball->vel.y *= -1;
  }

  mvaddch(ball->position.y, ball->position.x, 'O');
}
