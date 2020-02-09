#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "map_foo.h"
#include "declaration_header.h"
#include "new_stuff.h"

void print_map(unsigned long long map) {
	
	int k = 1, i = 8 * sizeof(unsigned long long) - 1, s = 1;
	unsigned long long mask;
	unsigned long long help = 1;

	//print the map converting the bits into # / .
	while ((k < 9) && (i >= 0)) {
		mask = (help << i);
		
		if ((map & mask) == mask) {
			printf("#");
			s++;
		}
		else printf(".");

		if (k == 8) {
			printf("\n");
			k = 0;
			s = 0;
		}
		k++;
		i--;
	}
	printf("\n");
}

//a function to check for completed lines and eliminate them from the map
void check_map(unsigned long long *map) {
	int k = 1, i = 8 * sizeof(unsigned long long) - 1, s = 0;
	unsigned char p = 0;

	unsigned long long mask, help = 1, help64 = 0;

	//print the map converting the bits into # / .
	while ((k < 9) && (i >= 0)) {
		mask = help << i;
		help64 = mask | help64;
		//increments s if we find a bit that's 1

		if (((*map) & mask) == mask) {
			s++;
		}

		//checking if a line on the map is completed
		//remove the line and make the bits 0 if that's true
		if (s == 8) {
			p = 1;
			completed_lines++;
			help64 = ~help64;

			if(i > 0) {
				(*map) = move_forward(*map, i);
			}//it works for i =0 , problem is up here
			else if(i == 0) {
				(*map) = (*map) >> 8;
			}
		}

		if (k == 8) {
			k = 0;
			s = 0;
			help64 = 0;
		}
		k++;
		i--;
	}
	//after we remove the completed lines, we print the new map configuration if we did any change
	if(p == 1)
		print_map(*map);
}

//a function that helps check_map to create the new map resulted by eliminating the completed line
unsigned long long move_forward(unsigned long long map, int t) {
	unsigned long long mask, help = 1, new_map = map >> 8;

	for(int j = t - 1; j >= 0; j--) {
		mask = help << j;
		if((mask & map) == mask) {
			new_map = new_map | mask;
		}
		else if((mask & map) != mask) {
			mask = ~(help << j);
			new_map = new_map & mask;
		}
	}
	return new_map;
}