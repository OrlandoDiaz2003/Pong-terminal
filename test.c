#include <math.h>
#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void finish(int sig);

typedef struct {
    float x;
    float y;

} Vector;

typedef struct {
    Vector position;
    Vector velocity;

} Ball;

typedef struct {
    Vector position;
    Vector velocity;

    int height;
} Paddle;

void ball_movement(Ball *ball) {
    // deleting the last draw of the ball
    mvaddch(ball->position.y, ball->position.x, ' ');

    // ball speed
    ball->position.x += ball-> velocity.x;
    ball-> position.y += ball-> velocity.y;

    // collision with borders
    bool collision_x = ball->position.x <= 0 || ball->position.x >= COLS - 1;
    bool collision_y = ball->position.y <= 0 || ball->position.y >= LINES - 1;

    if (collision_x) {
	ball-> velocity.x *= -1;
    }

    if (collision_y) {
	ball->velocity.y *= -1;

    }

    mvaddch(ball->position.y, ball->position.x, 'O');
}

void ball_collision_paddle(Paddle *paddle, Ball *ball) {
    bool collision_x = fabsf(ball -> position.x - paddle -> position.x) <= 1.5f;
    bool collision_y = (paddle->position.y <= ball->position.y) &&
	(paddle->position.y + paddle->height >= ball->position.y);

    if (collision_x && collision_y) {
	beep();
	ball->velocity.x *= -1;
    }
}

void draw_paddle(Paddle *paddle) {
    // Delete
    for (int i = 0; i < paddle->height; i++) {
	mvaddch(paddle->position.y + i, paddle->position.x, ' ');
    }
    // Draw paddle
    for (int i = 0; i < paddle->height; i++ ) {
	mvaddch(paddle->position.y + i, paddle->position.x, '#');
    }
}
void move_player_up(Paddle *player) {
    for (int i = 0; i < player->height; i++) {
	mvaddch(player-> position.y + i, player -> position.x, ' ');
    }

    if (player -> position.y >  2)
	player -> position.y = player -> position.y - 2.5;

    for (int i = 0; i < player -> height; i++) {
	mvaddch(player -> position.y + i, player -> position.x, '#');
    }

}

void move_player_down(Paddle *player) {
    for (int i = 0; i < player->height; i++) {
	mvaddch(player-> position.y + i, player -> position.x, ' ');
    }

    if (player -> position.y + player -> height < LINES - 2)
	player -> position.y = player -> position.y + 2.5;

    for (int i = 0; i < player -> height; i++) {
	mvaddch(player -> position.y + i, player -> position.x, '#');
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
	    move_player_up(player_1);
	    break;
	case 's':
	    move_player_down(player_1);
	    break;

	case KEY_UP:
	    move_player_up(player_2);
	    break;
	case KEY_DOWN:
	    move_player_down(player_2);
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
    Ball ball;
    ball.position.x = COLS / 8.0;
    ball.position.y = 0;

    ball.velocity.x = 1.0;
    ball.velocity.y = 0.5;

    // PADDLE
    Paddle player_1;
    player_1.position.x = 10;
    player_1.position.y = 20;
    player_1.height = 5;

    Paddle player_2;
    player_2.position.x = COLS - 10;
    player_2.position.y = 20;
    player_2.height = 5;

    draw_paddle(&player_1);
    draw_paddle(&player_2);
    for (;;) {
	//draw_area();
	controller(&player_1, &player_2);
	draw_paddle(&player_1);
	draw_paddle(&player_2);
	ball_movement(&ball);
	ball_collision_paddle(&player_1, &ball);
	ball_collision_paddle(&player_2, &ball);
	// paddle_collision(&player_2, &ball);

	refresh();
	usleep(15000);
    }

    finish(0);
}

static void finish(int sig) {
    endwin();

    exit(0);
}
