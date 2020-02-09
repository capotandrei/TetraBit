#ifndef MOVING_PARTS_FOO_H
#define MOVING_PARTS_FOO_H

#include "declaration_header.h"

int fit_the_piece(unsigned long long *map, unsigned char p, int t);
void let_the_game_begin(unsigned long long *map, PIECES *v, int number_pieces);
void convert_16_into_8(unsigned char *line1_8, unsigned char *line2_8, unsigned short int p);
void delete_prev_piece(unsigned long long *map, unsigned char p, int t);
void make_the_move8(unsigned long long *map, PIECES *p, int t, unsigned long long old_map);
void make_the_move16(unsigned long long *map, PIECES *p, int t, unsigned long long old_map);

#endif