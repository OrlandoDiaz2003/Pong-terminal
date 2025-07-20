#include <math.h>
#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void finish(int sig);

typedef struct {
  float pos_x;
  float pos_y;

  float vel_x;
  float vel_y;
} Ball;

typedef struct {
  float pos_x;
  float pos_y;

  float height;

} Paddle;

void update_ball(Ball *ball) {
  // deleting the last draw of the ball
  mvaddch(ball->pos_y, ball->pos_x, ' ');

  // ball speed
  ball->pos_x += ball->vel_x;
  ball->pos_y += ball->vel_y;

  // collision with borders
  bool collision_x = ball->pos_x <= 0 || ball->pos_x >= COLS - 1;
  bool collision_y = ball->pos_y <= 0 || ball->pos_y >= LINES - 1;

  if (collision_x) {
    ball->vel_x *= -1;
  }

  if (collision_y) {
    ball->vel_y *= -1;
  }
  // drawing ball in the new position
  mvaddch(ball->pos_y, ball->pos_x, 'O');
}

void paddle_collision(Paddle *paddle, Ball *ball) {
  bool collision_x = fabsf(ball->pos_x - paddle->pos_x) <= 1.5f;
  bool collision_y = (paddle->pos_y <= ball->pos_y) &&
                     (paddle->pos_y + paddle->height >= ball->pos_y);

  if (collision_x && collision_y) {
    beep();
    ball->vel_x *= -1;
  }
}

void paddle(Paddle *paddle) {
  // Delete
  for (int i = 0; i < paddle->height; i++) {
    mvaddch(paddle->pos_y + i, paddle->pos_x, ' ');
  }

  // Draw paddle
  for (int i = 0; i < paddle->height; i++) {
    mvaddch(paddle->pos_y + i, paddle->pos_x, '#');
  }
}

void controller(Paddle *player_1, Paddle *player_2) {
  int key = getch();
  int start_x, start_y, height, withd;

  height = 30;
  withd = 90;
  start_x = (COLS - withd)/2;
  start_y = (LINES - height)/2;

  switch (key) {
  // player 1
  case 'w':
    for (int i = 0; i < player_1->height; i++) {
      mvaddch(player_1->pos_y + i, player_1->pos_x, ' ');
    }

    if (player_1->pos_y > start_y + 2)
      player_1->pos_y = player_1->pos_y - 2.5;

    for (int i = 0; i < player_1->height; i++) {
      mvaddch(player_1->pos_y + i, player_1->pos_x, '#');
    }
    break;
  case 's':
    for (int i = 0; i < player_1->height; i++) {
      mvaddch(player_1->pos_y + i, player_1->pos_x, ' ');
    }

    if (player_1->pos_y + player_1->height < height - 1)
      player_1->pos_y = player_1->pos_y + 2.5;

    for (int i = 0; i < player_1->height; i++) {
      mvaddch(player_1->pos_y + i, player_1->pos_x, '#');
    }
    break;

  case KEY_UP:
    for (int i = 0; i < player_2->height; i++) {
      mvaddch(player_2->pos_y + i, player_2->pos_x, ' ');
    }

    if (player_2->pos_y > start_y + 2)
      player_2->pos_y = player_2->pos_y - 2.5;

    for (int i = 0; i < player_2->height; i++) {
      mvaddch(player_2->pos_y + i, player_2->pos_x, '#');
    }
    break;
  case KEY_DOWN:
    for (int i = 0; i < player_2->height; i++) {
      mvaddch(player_2->pos_y + i, player_2->pos_x, ' ');
    }

    if (player_2->pos_y + player_2->height < height - 1)
      player_2->pos_y = player_2->pos_y + 2.5;

    for (int i = 0; i < player_2->height; i++) {
      mvaddch(player_2->pos_y + i, player_2->pos_x, '#');
    }
    break;
  }
}

void draw_area() {
  int start_y, start_x, withd, height;

  height = LINES - 10;
  withd = COLS - 20;
  start_x = (COLS - withd)/2;
  start_y = (LINES - height)/2;

  WINDOW *win = newwin(height, withd, start_y, start_x);

  box(win, '*', '*');
  touchwin(win);
  wrefresh(win);
}

int main() {
  initscr();

  nodelay(stdscr, TRUE);
  signal(SIGINT, finish);

  keypad(stdscr, TRUE);
  noecho();
  cbreak();

  // key
  int key = getch();

  // BALL VARIABLES
  // ball position
  float ball_y = 0;
  float ball_x = COLS / 8.0;

  Ball ball;
  ball.pos_x = COLS / 8.0;
  ball.pos_y = 0;

  ball.vel_x = 1.0;
  ball.vel_y = 0.5;

  // PADDLE
  Paddle player_1;
  player_1.pos_x = 100/2.0 - 10;
  player_1.pos_y = LINES/2.0;
  player_1.height = 4;

  Paddle player_2;
  player_2.pos_x = (100/2.0 + 100/2.0) + 19;
  player_2.pos_y = LINES/2.0;
  player_2.height = 4;

  for (;;) {
    draw_area();
    // update_ball(&ball);
    // paddle_collision(&player_1, &ball);
    // paddle_collision(&player_2, &ball);
    controller(&player_1, &player_2);
    paddle(&player_1);
    paddle(&player_2);

    refresh();
    usleep(15000);
  }

  finish(0);
}

static void finish(int sig) {
  endwin();

  exit(0);
}
