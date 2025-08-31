#include "../include/ball.h"
#include "../include/game.h"
#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>

void ball_init(Ball *ball) {
  ball->position.x = WIDTH / 2.0;
  ball->position.y = HEIGHT / 2.0;
  ball->vel.x = 0.5;
  ball->vel.y = 0;
  ball->acceleration = 0.1;
}

void ball_movement(Ball *ball) {
  // deleting the last draw of the ball
  mvaddch(ball->position.y, ball->position.x, ' ');

  ball->position.x += ball->vel.x;
  ball->position.y += ball->vel.y;

  bool collision_x = ball->position.x <= 0 || ball->position.x >= WIDTH - 1;
  bool collision_y = ball->position.y <= 0 || ball->position.y >= HEIGHT - 1;

  if (collision_x) {
    ball->position.x = WIDTH / 2.0;
    ball->vel.x *= -1;
  }

  if (collision_y) {
    ball->vel.y *= -1;
  }

  mvaddch((int)ball->position.y, (int)ball->position.x, 'O');
}
