#include "../include/player.h"
#include "../include/game.h"
#include <ncurses.h>

void init_player(Player *player) {
  player->player_pos.x = 10;
  player->player_pos.y = 20;
  player->player_vel = 1;
  player->height = 6;
  player->score = 0;
}

void player_controller(Player *player1, Player *player2) {

  int key = getch();
  switch (key) {
  case 'w':
    move_player_up(player1);
  case 's':
    move_player_down(player1);
  case KEY_UP:
    move_player_up(player2);
  case KEY_DOWN:
    move_player_down(player2);
  }
}
void move_player_up(Player *player) {
  // deleting player last position
  for (int i = 0; i < player->height; ++i)
    mvprintw(player->player_pos.y + i, player->player_pos.x, " ");

  if (player->player_pos.y > 0) {
    player->player_pos.y -= player->player_vel;
  }
  for (int i = 0; i < player->height; ++i)
    mvprintw(player->player_pos.y + i, player->player_pos.x, " ");
}

void move_player_down(Player *player) {
  // deleting player last position
  for (int i = 0; i < player->height; ++i)
    mvprintw(player->player_pos.y + i, player->player_pos.x, " ");

  if (player->player_pos.y + player->height < HEIGHT - 1)
    player->player_pos.y += player->player_vel;

  for (int i = 0; i < player->height; ++i)
    mvprintw(player->player_pos.y + i, player->player_pos.x, " ");
}
