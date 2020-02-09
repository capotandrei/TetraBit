#ifndef DECLARATION_HEADER
#define DECLARATION_HEADER

extern int completed_lines;

//an union to manage better and storage the variables depending on their types
typedef union {
	unsigned short int tempo_16;
	unsigned char tempo_8;
} UNION;

typedef struct {
	//i used the contor to figurre out what kind of type is the temp variable
	int contor;
	int moves[8];
	UNION temp;

} PIECES;

#endif