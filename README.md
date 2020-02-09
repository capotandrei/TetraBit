# TetraBit

# Introduction
TetraBit is a small game written in C. It uses the idea of a Tetris game using bitwise operations.

# The Map
To draw the Tetris map, we used the bit representation of a long number on 64 bits (unsigned long long) like this:
  - bits of 1 are occupied areas
  - bits of 0 are unoccupied areas
For example, for “284 803 830 071 167”, whose representation in bits is:

00000000 00000001 00000011 00000111 00001111 00011111 00111111 01111111

We build the following map:

        ........
        
        .......#
        
        ......##
        
        .....###
        
        ....####
        
        ...#####
        
        ..######
        
        .#######
        
        
# How the game works ? 
-> Pieces: You can have different pieces that are also a representation in bits of a number. 

...#....

or  


.##..... 

.#......

-> Moving of a piece: Every sesion in this game contains a number of moves. Every move contains the current piece and its transformations: one transformation for each line of the map.
For example, if we have this move: 6168 -1 2 -2 0 0 1 1 -3 , where the piece looks like this:

...##...

...##...
                                                                                              
A transformation -6 produce to this piece this result: 

                                                       ##......

                                                       ##......

-> Empty a completed line: If a line is full: ######## , then the line gets empty.

# When it's GAME OVER ?
1. All the moves were made.
2. The piece has no space on the map.
       

 
