#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <math.h>

//headers
#include "map_foo.h"
#include "moving_parts_foo.h"
#include "declaration_header.h"
#include "new_stuff.h"

//a variable used to count the completed lines during the game
int completed_lines = 0;

PIECES *get_the_moves(int number_pieces);

int main() {
	unsigned long long map;
	scanf("%llu", &map);

	//reading the number of pieces from stdin
	int number_pieces;
	scanf("%d", &number_pieces);

	PIECES *v = get_the_moves(number_pieces);

	//a function that prints the map using the ./# format
	print_map(map);
	//main function where every dream becomes true :D
	let_the_game_begin(&map, v, number_pieces);
	//print the score based on a specific formula given in the requirement
	easy_win_score(map);

	return 0;
}

PIECES *get_the_moves(int number_pieces) {

	PIECES *v = malloc(number_pieces * sizeof(PIECES));

	unsigned short int temp_16, mask, help16 = 1;
	unsigned char temp_8 = 0, bop, help8 = 1;
	for(int ct = 0; ct < number_pieces; ct++) {
		temp_8 = 0;
		//reading the piece on 16 bits (checking after if we need to convert it into 8)
		scanf("%hu", &temp_16);
		//reading the moves of the pieces
		for(int t = 0; t < 8; t++) {
			scanf("%d", &v[ct].moves[t]);
		}
		if (temp_16 <= 255) {
			for(int i = 7; i >= 0; i--) {
				//prepare the variables to convert 16 bits type into 8
				mask = help16 << i;
				bop = help8 << i;

				if((temp_16 & mask) == mask) {
					temp_8 = temp_8 | bop;
				}
			}
			v[ct].temp.tempo_8 = temp_8;
			v[ct].contor = 8;
		} 
		else { 
			v[ct].temp.tempo_16 = temp_16;
			v[ct].contor = 16;
		}
	}
	//then returning the vector that include all the pieces associated with their 8 moves for each one
	return v;
}
