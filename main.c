#include "./include/game.h"
#include "./include/player.h"
#include "./include/ball.h"
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void finish(int sig);

int main(){

    initscr();

    nodelay(stdscr, TRUE);
    signal(SIGINT, finish);

    keypad(stdscr, TRUE);
    noecho();
    cbreak();
	Ball ball;
	Player player_1;
	Player player_2;

	init_player(&player_1, &player_2);
	ball_init(&ball);

	while(1){
		draw_center_line();
		player_controller(&player_1, &player_2);
		ball_movement(&ball);
		player_collision_ball(&player_1, &ball);
		player_collision_ball(&player_2, &ball);
		player_score(&player_1, &player_2,&ball);

		usleep(15000);
	}

    finish(0);
};

static void finish(int sig) {
    endwin();

    exit(0);
}
