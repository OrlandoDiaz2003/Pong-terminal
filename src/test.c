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
    int velocity;

    int height;
    int score;
} Paddle;

void ball_movement(Ball *ball, Paddle *player_1,Paddle *player_2) {
    // deleting the last draw of the ball
     mvaddch(ball->position.y, ball->position.x, ' ');
     
    // ball speed
    ball->position.x += ball-> velocity.x;
    ball-> position.y += ball-> velocity.y;

    // collision with borders
    bool collision_x = ball->position.x <= 0 || ball->position.x >= COLS - 1;
    bool collision_y = ball->position.y <= 0 || ball->position.y >= LINES - 1;

    //score checking
    if(ball->position.x >= COLS - 1) player_1 -> score += 1;
    if(ball->position.x <= 0) player_2 -> score += 1;

    if (collision_x) {
        
	ball -> position.x = COLS/2.0;
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
	    int hit = ball->position.y - (paddle->position.y - (paddle->height/2.0));
           mvprintw(10,20,"hit : %d", hit);

	    bool center = hit == 5;
	    bool high = hit <= 4 && hit >= 3;
	    bool low = hit > 5 && hit <= 8; 
	    //
	    if(center) ball->velocity.y = 0;
	    if(high) ball->velocity.y -= 0.2;
	    if(low) ball->velocity.y += 0.2;

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

    if (player -> position.y >  0)
	player -> position.y -= player -> velocity;

    for (int i = 0; i < player -> height; i++) {
	mvaddch(player -> position.y + i, player -> position.x, '#');
    }

}

void move_player_down(Paddle *player) {
    for (int i = 0; i < player->height; i++) {
	mvaddch(player-> position.y + i, player -> position.x, ' ');
    }

    if (player -> position.y + player -> height < LINES - 1)
	player -> position.y += player -> velocity;

    for (int i = 0; i < player -> height; i++) {
	mvaddch(player -> position.y + i, player -> position.x, '#');
    }

}
void controller(Paddle *player_1, Paddle *player_2) {
    int key = getch();

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

void show_score(Paddle * player_1, Paddle * player_2){
     int score_1 = player_1 -> score;
     int score_2 = player_2 -> score;

     mvprintw(0, 10, "Player 1: %d",score_1);
     mvprintw(0, COLS - 20, "Player 2: %d",score_2);
}
void center_line() {
    for(int i = 0; i < LINES; i ++){
	mvprintw(LINES - i, COLS/2,"|");
    }
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

    //Ball
    Ball ball;
    ball.position.x = COLS / 2.0;
    ball.position.y = LINES/2.0;

    ball.velocity.x = 0.5;
    ball.velocity.y = 0;

    //Paddles
    Paddle player_1;
    player_1.position.x = 10;
    player_1.position.y = 20;
    player_1.velocity = 1;
    player_1.height = 6;
    player_1.score = 0;

    Paddle player_2;
    player_2.position.x = COLS - 10;
    player_2.position.y = 20;
    player_2.velocity = 1;
    player_2.height = 6;
    player_2.score = 0;

    for (;;) {

	center_line();
	controller(&player_1, &player_2);
	draw_paddle(&player_1);
	draw_paddle(&player_2);
	ball_movement(&ball,&player_1, &player_2);
	ball_collision_paddle(&player_1, &ball);
	ball_collision_paddle(&player_2, &ball);
	show_score(&player_1, &player_2);
	refresh();
	usleep(15000);
    }

    finish(0);
}

static void finish(int sig) {
    endwin();

    exit(0);
}
