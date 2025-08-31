#include "../include/player.h"
#include "../include/game.h"
#include <ncurses.h>

void init_player(Player *player1, Player *player2) {
  player1->player_pos.x = 10;
  player1->player_pos.y = 20;
  player1->player_vel = 2;
  player1->height = 6;
  player1->score = 0;

  player2->player_pos.x = WIDTH - 10;
  player2->player_pos.y = 20;
  player2->player_vel = 2;
  player2->height = 6;
  player2->score = 0;

  // player_1 
  for (int i = 0; i < player1->height; ++i)
    mvprintw(player1->player_pos.y + i, player1->player_pos.x, " ");

  for (int i = 0; i < player1->height; ++i)
    mvprintw(player1->player_pos.y + i, player1->player_pos.x, "#");

	//player_2
  for (int i = 0; i < player2->height; ++i)
    mvprintw(player2->player_pos.y + i, player2->player_pos.x, " ");

  for (int i = 0; i < player2->height; ++i)
    mvprintw(player2->player_pos.y + i, player2->player_pos.x, "#");
}

void player_controller(Player *player1, Player *player2) {

  int key = getch();
  switch (key) {
  case 'w':
    move_player_up(player1);
		break;
  case 's':
    move_player_down(player1);
		break;
  case KEY_UP:
    move_player_up(player2);
		break;
  case KEY_DOWN:
    move_player_down(player2);
		break;
  }
}

void draw_player(Player *player) {
  // deleting player last position
  for (int i = 0; i < player->height; ++i)
    mvprintw(player->player_pos.y + i, player->player_pos.x, " ");

  for (int i = 0; i < player->height; ++i)
    mvprintw(player->player_pos.y + i, player->player_pos.x, "#");
}

void move_player_up(Player *player) {
  // deleting player last position
  for (int i = 0; i < player->height; ++i)
    mvprintw(player->player_pos.y + i, player->player_pos.x, " ");

  if (player->player_pos.y > 0) {
    player->player_pos.y -= player->player_vel;
  }
  for (int i = 0; i < player->height; ++i)
    mvprintw(player->player_pos.y + i, player->player_pos.x, "#");
}

void move_player_down(Player *player) {
  // deleting player last position
  for (int i = 0; i < player->height; ++i)
    mvprintw(player->player_pos.y + i, player->player_pos.x, " ");

  if (player->player_pos.y + player->height < HEIGHT - 1)
    player->player_pos.y += player->player_vel;

  for (int i = 0; i < player->height; ++i)
    mvprintw(player->player_pos.y + i, player->player_pos.x, "#");
}
