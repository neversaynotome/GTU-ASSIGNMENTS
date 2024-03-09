/*
** main.c:
**
** The test/driver program for the homework.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.22.19.55
** 
*/


#include <stdio.h>
#include "hw8_lib.h"


void test_clean_file () 
{
	printf("\n'test_clean_file' IS NOT IMPLEMENTED\n");
}


void test_maze_move ()
{
	printf("\n'test_maze_move' IS NOT IMPLEMENTED\n\n");
}


void test_towers_of_hanoi ()
{
	int n = 5;							/* number of disks			*/	/* Because of my visas i had very limited time for this homework */
	towers_of_hanoi('A','C','B',n);		/* 1:start 2:end 3:auxiliary*/	/* with this very limited time, i only came up with this super-basic */
}																		/* recursive implemantation for this part */


/*
** main function for testing the functions...
**
*/
int main(void) {
	test_clean_file ();
	test_maze_move ();
	test_towers_of_hanoi ();
	return (0);
} /* end main */
