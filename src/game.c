#include "../include/game.h"
#include "../include/ball.h"
#include "../include/player.h"
#include <math.h>
#include <ncurses.h>
#include <stdint.h>

void player_collision_ball(Player *player, Ball *ball) {
  bool collision_x = fabsf(ball->position.x - player->player_pos.x) <= 1.5;
  bool collision_y =
      (player->player_pos.y <= ball->position.y ) &&
      (player->player_pos.y + player->height >= ball->position.y);

        mvprintw(10,10,"ball_pos_x: %f", ball->position.x);
        mvprintw(10,60,"ball_pos_y: %f", ball->position.y);
        mvprintw(20,60,"ball_vel_y: %f", ball->vel.y);
        mvprintw(20,60,"ball_vel_x: %f", ball->vel.x);
	if (collision_x && collision_y) {
	    int hit = ball->position.y - (player->player_pos.y - (player->height/2.0));

	    bool center = hit == 5;
	    bool high = hit <= 4 && hit >= 3;
	    bool low = hit > 5 && hit <= 8; 
	    //
	    if(center) ball->vel.y = 0;
	    if(high) ball->vel.y -= 0.2;
	    if(low) ball->vel.y += 0.2;

	    beep();
	    ball->vel.x *= -1;
        mvprintw(10,100,"hit: %d", hit);

	}
}

void player_score(Player *player1, Player *player2, Ball *ball) {
  if (ball->position.x >= WIDTH - 1)
    player1->score += 1;
  if (ball->position.x <= 0)
    player2->score += 1;

  mvprintw(0, 10, "Player 1: %d", player1->score);
  mvprintw(0, WIDTH - 20, "Player 2: %d", player2->score);
}

void draw_center_line() {
	for(int i = 0; i < LINES; i ++){
		mvprintw(LINES - i, COLS/2,"|");
	}
};
