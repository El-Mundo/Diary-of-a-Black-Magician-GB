#include <stdio.h>

UINT8 collision(UINT8 x1, UINT8 y1, UINT8 w1, UINT8 h1, UINT8 x2, UINT8 y2, UINT8 w2, UINT8 h2);
UINT8 spawn_enemy(UINT8 num, UINT8 type, UINT8 x, UINT8 y);
UINT8 update_frame(UINT8 player_frame);
UINT8 erase_enemy(UINT8 num);
UINT8 update_effect();
void perform_delay(UINT8 time);