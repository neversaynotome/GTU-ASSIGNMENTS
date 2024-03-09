/*
** hw8_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.22.19.55
** 
*/

#include <stdio.h>
#include "hw8_lib.h"

#define WORDSIZE 1


void delete_words (FILE* infid, FILE* outfid, char* words_to_delete[WORDSIZE],  int number_of_words)
{
	/* IS NOT IMPLEMENTED */
}


void clean_file(char* infile, char * outfile, char* words_to_delete[WORDSIZE], int number_of_words)
{
	FILE infid, outfid;
	delete_words (&infid, &outfid, words_to_delete, number_of_words);
	/* IS NOT IMPLEMENTED */
}


int maze_move(cell_type maze[][8], cell_type player, move_type move)
{
	/* IS NOT IMPLEMENTED */
	return -1;
}


void towers_of_hanoi(char start_peg, char end_peg, char aux_peg, int n)
{
    if(n>0){																/* Because of my visas i had very limited time for this homework */
    towers_of_hanoi(start_peg,aux_peg,end_peg,n-1);							/* with this very limited time, i only came up with this super-basic */
    printf("Move the %d.disk from %c to %c.\n",n,start_peg,end_peg);		/* recursive implemantation for this part */
    towers_of_hanoi(aux_peg,end_peg,start_peg,n-1);
	}
}
