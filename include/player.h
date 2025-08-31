#ifndef PLAYER_H_ 
#define PLAYER_H_ 
#include <stdint.h>
#include <stdio.h>
#include "../include/vector.h"

typedef struct {
  Vector player_pos;
  uint_fast8_t height;

  float player_vel;
  int score;

} Player;

void init_player(Player *player1, Player *player2);
void move_player_up(Player *player);
void move_player_down(Player *player);
void player_controller(Player *player1, Player *player2);
void draw_player(Player *player);

#endif
