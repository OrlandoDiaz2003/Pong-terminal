#include "vector.h"
#include <cstdint>
#include <stdio.h>

typedef struct {
  Vector player_pos;
  int height;

  float player_vel;
  uint32_t score;

} Player;

void init_player(Player *player);
void move_player(Player *player);
void draw_player(Player *player);
