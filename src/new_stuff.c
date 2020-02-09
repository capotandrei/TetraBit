#include "new_stuff.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "declaration_header.h"

//convert from 64 bits -> 8 bits
unsigned char convert_into_8(unsigned long long p64, int t) {
	unsigned long long mask64, help64 = 1;
	unsigned char mask, help = 1, new_piece = 0;
	int k = 7;
	if(t > 1) {
		for(size_t i = t * sizeof(unsigned long long) - 1; i >= (t - 1) * sizeof(unsigned long long); i--) {
			mask = help << k;
			mask64 = help64 << i;
			if((mask64 & p64) == mask64) {
				new_piece = new_piece | mask;
			}
			k--;
		}
	} else {
		if(t == 1) {
			for(int j = 7; j >= 0; j--) {
				mask = help << k;
				mask64 = help64 << j;
				if((mask64 & p64) == mask64) {
					new_piece = new_piece | mask;
				}
			k--;
			}
		}
	}
	return new_piece;
}

//convert from 64 bits -> 16 bits
unsigned short int convert_into_16(unsigned long long p64, int t) {
	unsigned long long mask64, help64 = 1;
	unsigned short int mask, help = 1, new_piece = 0;
	int k = 15;

	if(t > 1 && t < 8) {
		for(int i = (t + 1) * sizeof(unsigned long long) - 1; i >= (t - 1) * sizeof(unsigned long long); i--) {
			mask64 = help64 << i;
			mask = help << k;
			if((mask64 & p64) == mask64) {
				new_piece = new_piece | mask;
			}
			k--;
		}
	} else {
		if(t == 1) {
			k = 15;
			for(int j = 15; j >= 0; j--) {
				mask64 = help64 << j;
				mask = help << k;
				if((mask64 & p64) == mask64) {
					new_piece = new_piece | mask;
				}
				k--;
			}
		}
	}
	if(t == 8) {
		k = 7;
		for(int i = t * sizeof(unsigned long long) - 1; i >= (t - 1) * sizeof(unsigned long long); i--) {
			mask64 = help64 << i;
			mask = help << k;
			if((mask64 & p64) == mask64) {
				new_piece = new_piece | mask;
			}
			k--;
		}
	}
	return new_piece;
}

void easy_win_score(unsigned long long map) {
	unsigned long long mask, help = 1;
	int k = 0;
	//counting the number of bits equal to 0
	for(int j = 8 * sizeof(unsigned long long) - 1; j >= 0; j--) {
		mask = help << j;

		if((mask & map) != mask) {
			k++;
		}
	}
	float score = sqrt(k) + pow(1.25, completed_lines);

	puts("GAME OVER!");
	printf("Score:%.2f\n", score);

}