#include "moving_parts_foo.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "declaration_header.h"
#include "map_foo.h"
#include "new_stuff.h"

//the main function which combine all the functions that are necessary to move pieces, print the map, check for completed lines etc
void let_the_game_begin(unsigned long long *map, PIECES *v, int number_pieces) {
	int t, contor2;

	for(int i = 0; i < number_pieces; i++) {
		t = 8;
	//first verify if the piece fits in the map
		switch(v[i].contor) {
			case 16 : {
				contor2 = 8;
				unsigned char line1_8 = 0, line2_8 = 0;
				//break the 16 bits piece into two 8 bits piece so i can use fit_the_piece & delete_prev_piece for both 8 & 16 bits pieces
				convert_16_into_8(&line1_8, &line2_8, v[i].temp.tempo_16);
				//save the old value of the map, need this for the make_the_move function
				unsigned long long old_map = (*map);
				//check if the first 8 bits piece fits(using fit_the_piece function) and complete the map if it does
				while(t > 0 && contor2 > 1) {
					if(fit_the_piece(&(*map), line1_8, t) != 0) {
						if(t == 8) {
							//if it's only the first line, move the piece and print the map
							make_the_move16(&(*map), &v[i], t, old_map);
							convert_16_into_8(&line1_8, &line2_8, v[i].temp.tempo_16);
							old_map = (*map);
							print_map(*map);
						}
						if(t < 8) {
							//delete_prev_piece is a function that deletes the piece from the previous line
							delete_prev_piece(&(*map), line1_8, t);
							//check if secound 8 bits piece also fits
							if(fit_the_piece(&(*map), line2_8, contor2) != 0) {
								if(contor2 < 8) {
									delete_prev_piece(&(*map), line2_8, contor2);
								}
								//move the piece
								make_the_move16(&(*map), &v[i], t, old_map);
								convert_16_into_8(&line1_8, &line2_8, v[i].temp.tempo_16);
								old_map = (*map);
								print_map(*map);
								contor2--;
							}
							else {
								//if line2_8 doesnt fit, this means that the entire piece doesn't fit
								//so undo the fit_the_piece for line1_8 and move the piece back where it stopped
								fit_the_piece(&(*map), line1_8, t + 1);
								delete_prev_piece(&(*map), line1_8, t - 1);
								//after the piece is where it belongs, we check the map for completed lines and eliminate them
								check_map(&(*map));
								break;
							}
						}
						t--;
					}
					else {
						if(t == 8) {
							print_map(*map);
							easy_win_score(*map);
							exit(1);
						}
						check_map(&(*map));
						break;
					} 
				}
				//after the piece is where it belongs, we check the map for completed lines and eliminate them
				check_map(&(*map));

				break;
			}

			case 8 : {
				//make a copy of the map before the piece is moved so the make_the_move function will work properly
				unsigned long long old_map = (*map);
				//check if the piece fits and complete the map if it does
				while(t > 0) {
					//Same as it was for case 16
					if(fit_the_piece(&(*map), v[i].temp.tempo_8, t) != 0) {
						if(t < 8) {
                            delete_prev_piece(&(*map), v[i].temp.tempo_8, t);
                        }
                           	make_the_move8(&(*map), &v[i], t, old_map);
							print_map(*map);
							old_map = (*map);
							t--;
					}
					else { 
						if(t == 8) {
							print_map(*map);
						}
						check_map(&(*map));
						break;
					}
				}
				check_map(&(*map));
				break;
			}

			default : {
				puts("Contor is wrong ! Check the vector !");
				break;
			}
		}
	}
}

void convert_16_into_8(unsigned char *line1_8, unsigned char *line2_8, unsigned short int p) {
	(*line1_8) = 0;
	(*line2_8) = 0;
	unsigned char mask8, help8 = 1;
	unsigned short int mask16, help16 = 1;
	//i tried to break the 16 bits var in two 8 bits tempo variables and check both lines in the function
	for(int l = 15; l >= 0; l--) {
			mask16 = help16 << l;
			if((mask16 & p) == mask16) {
				if(l <= 7) {
					mask8 = help8 << l;
					(*line1_8) = (*line1_8) | mask8;
				}
				else {
					mask8 = help8 << (l - 8);
					(*line2_8) = (*line2_8) | mask8;
					}
				}
	}
}

//a function to check if the piece fits and complete the next line in case it fits
int fit_the_piece(unsigned long long *map, unsigned char p, int t) {
	unsigned long long map_mask, bop = 1;

	//first verify if the piece fits in the map
		int k = 7;
		unsigned char mask8, help8 = 1;
		unsigned long long help64 = 1, mask64 = 0;
		
		//checking the bits from the first column of the map
		if(t > 1) {
			for(size_t j = t * sizeof(unsigned long long) - 1; j >= (t - 1) * sizeof(unsigned long long); j--) {
				map_mask = help64 << j;
				//checking bit by bit and return 0(not fitting) if we see any bit equal
				if((map_mask & (*map)) == map_mask) {
					mask8 = help8 << k;
					if((mask8 & p) == mask8)
						return 0;
				}
				k--;
			}
		}

		// size_t doesnt work for the t = 1 case, so i tried to use an integer until i fix the problem
		// *later edit* i fixed the problem, that's why i need to use this integer variable for 't = 1' case
		k = 7;
		if(t == 1) {
            for(int q = 7; q >= 0; q--) {
               map_mask = help64 << q;
			//checking bit by bit and return 0(not fitting) if we see any bit equal
                if((map_mask & (*map)) == map_mask) {
                    mask8 = help8 << k;
                    if((mask8 & p) == mask8)
                        return 0;
                }
                k--;
            }
		}

		int d = t * sizeof(unsigned long long) - 1;
		for(int  i = 8 * sizeof(unsigned char) - 1; i >= 0; i--) {
			mask8 = help8 << i; 
			if((mask8 & p) == mask8) {
				mask64 = bop << d;
				(*map) = (*map) | mask64;
			}
			d--;
		}
		return 1;
}

//delete the piece from the previous line
void delete_prev_piece(unsigned long long *map, unsigned char p, int t) {
    unsigned long long map_mask, help64 = 1;
    unsigned char mask8, help8 = 1;
    int k = 7;
    //delete the piece from the specified line (t + 1), cause now it will appear on t
    if(t < 8 && t > 1) {
        for(size_t j = (t + 1) * sizeof(unsigned long long) - 1; j >= t * sizeof(unsigned long long); j--) {
            map_mask = ~(help64 << j);
            mask8 = help8 << k;
            if((mask8 & p) == mask8) {
            	(*map) = (*map) & map_mask;
        	}
            k--;
        }
    }
  	//the 't == 1' case that needs special treatment, using an integer instead of size_t
    else if(t == 1) {
       		k = 7;
        	for(int i = 15; i >= 8; i--) {
            	map_mask = ~(help64 << i);
            	mask8 = help8 << k;
            	if((mask8 & p) == mask8) {
            		(*map) = (*map) & map_mask;
        		}
           		k--;
        	}
    	}
    	else puts("Something is wrong ! Check the delete function !");
}

//move the piece while it's possible(the 8 bits one)
void make_the_move8(unsigned long long *map, PIECES *p, int t, unsigned long long old_map) {
	if((*p).contor == 8) {
		//connverting the piece into a 64 bits piece 
		unsigned long long p64 = (*p).temp.tempo_8, help64 = 1, mask, copy;
		if(t != 1)
			p64 = p64 << ((t - 1) * sizeof(unsigned long long));
		//saving the old value
		mask = p64;
		//test is a contor to check if move!= 0 and only then changing the map in the end
		int contor, test = 0;

		switch(((*p).moves[8 - t] > 0)? 1 : 0) {
			case 1:
				test = 1;
				unsigned long long pstop = help64 << ((t - 1) * sizeof(unsigned long long));
				contor = 1;

				if((p64 & pstop) == 0) {
					while(contor <= (*p).moves[8 - t]) {
						copy = p64 >> 1;
						if((copy & old_map) == 0) {
							p64 = copy;
							contor++;
						}
						else break;
						//check if the move is too long
						if((p64 & pstop) != 0) {
							break;
						}
					}
				}
			break;

			case 0:
				if((*p).moves[8 - t] < 0) {
					test = 1;
					unsigned long long nstop = help64 << (t * sizeof(unsigned long long) - 1);
					contor = 1;

					if((p64 & nstop) == 0) {
						while(contor <= abs((*p).moves[8 - t])) {
							copy = p64 << 1;

							if((copy & old_map) == 0) {
								p64 = copy;
								contor++;
							}
							else break;
							//check if the move is too long
							if((p64 & nstop) != 0)
								break;
						}
					}
				}
			break;

			default:
				puts("Something is wrong ! Check the function *make_the_move8*");
				break;
		}

		if(test != 0) {
			//deleting the piece from where it was in the first place
			mask = ~mask;
			(*map) = (*map) & mask;
			//moving the piece on the map
			(*map) = (*map) | p64;
			//replacing the piece with the new one resulted by moving
			(*p).temp.tempo_8 = convert_into_8(p64, t);
		}
	}
}

//move the piece while it's possible(the 16 bits one)
void make_the_move16(unsigned long long *map, PIECES *p, int t, unsigned long long old_map) {
	if((*p).contor == 16) {
		unsigned long long p64 = (*p).temp.tempo_16, help64 = 1, mask, copy, temps;
		if(t != 1) {
			p64 = p64 << ((t - 1) * sizeof(unsigned long long));
		}
		//saving the old value
		mask = p64;
		temps = p64;
		//test is a contor to check if move!= 0 and only then changing the map in the end
		int contor, test = 0;
		old_map = (*map) & (~temps);

		switch(((*p).moves[8 - t] > 0)? 1 : 0) {
			case 1:
				test = 1;
				unsigned long long pstop, pstop1 = help64 << ((t - 1) * sizeof(unsigned long long)), pstop2 = 0;
				if(t != 8) {
					pstop2 = help64 << (t * sizeof(unsigned long long));
				}
				pstop = pstop1 | pstop2;
				contor = 1;
				if((p64 & pstop) == 0) {
					while(contor <= (*p).moves[8 - t]) {
						copy = p64 >> 1;
						if((copy & old_map) == 0) {
							p64 = copy;
							contor++;
						}
						else break;
						//check if the move is too long
						if((p64 & pstop) != 0) {
							break;
						}
					}
					if(t == 8) {
						(*p).temp.tempo_16 = (*p).temp.tempo_16 >> (contor - 1);
					}
				}
			break;

			case 0:
				if((*p).moves[8 - t] < 0) {
					test = 1;
					unsigned long long nstop1 = help64 << ((t + 1) * sizeof(unsigned long long) - 1), nstop, nstop2;
					nstop2 = help64 << (t * sizeof(unsigned long long) - 1);
					if(t == 8) {
						nstop1 = help64 << (t * sizeof(unsigned long long) - 1);
					}
					nstop = nstop2 | nstop1;
					contor = 1;
					if((p64 & nstop) == 0) {
						while(contor <= abs((*p).moves[8 - t])) {
							copy = p64 << 1;
							if((copy & old_map) == 0) {
								p64 = copy;
								contor++;
							}
							else break;
							//check if the move is too long
							if((p64 & nstop) != 0)
								break;
						}
					}
					if(t == 8) {
						(*p).temp.tempo_16 = (*p).temp.tempo_16 << (contor - 1);
					}
				}
			break;

			default:
				puts("Something is wrong ! Check the function *make_the_move16*");
				break;
		}
		if(test != 0) {
			//deleting the piece from where it was in the first place
			mask = ~mask;
			(*map) = (*map) & mask;
			//moving the piece on the map
			(*map) = (*map) | p64;
			//replacing the piece with the new one resulted by moving
			if(t != 8) {
				(*p).temp.tempo_16 = convert_into_16(p64, t);
			}
		}	
	}
}
