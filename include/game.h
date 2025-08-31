#include "../include/ball.h"
#include "../include/player.h"
#include "../include/vector.h"
#include <ncurses.h>
#define WIDTH COLS
#define HEIGHT LINES

void player_collision_ball(Player *player, Ball *ball);
void player_score( Player *player2, Player *player1, Ball *ball);

void draw_center_line();

