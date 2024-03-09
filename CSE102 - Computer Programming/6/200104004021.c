#include <stdio.h>
#include <stdlib.h>
#define N 3

void create_array(int puzzle [][N]);			/* To create the array */
int  is_possible(int puzzle [][N]);				/* Works with "create_array" to ensure that puzzle will be solveable */
void print_array(int puzzle [][N]);				/* Prints the array as a table */
void swap(int puzzle [][N]);					/* According to user input the modifies the puzzle */
void done(int puzzle [][N], int *completed);	/* Checks if the puzzle is done or not */

void main(void){

	int puzzle [N][N],completed;				/* "puzzle" will store the numbers that will be used in the sliding puzzle */
												/* "completed" is modified by function "done" and used in main to ask for inputs */
	create_array(puzzle);
	
	do{											/* Untıl the puzzle is done it will print the table, ask for inputs and check if the puzzle is finished */
		print_array(puzzle);
		swap(puzzle);
		done(puzzle,&completed);
	} while(completed == 0);

	print_array(puzzle);								/* if puzzle is finished, the table will be printed for the last time */
	printf("Well done, the puzzle is completed.\n");

}

/*---------------------------------------------------------------------------------------------*/

void create_array(int puzzle [][N]){

	int i,j,v=0,k,temp;	srand((long int)&temp);			/* Using type cast and address of a random variable (temp is used in this case) randomized outputs are achieved */

		for (i = 0; i < N; i++)							/* Fills the array from 0 to N*N */
		for (j = 0; j < N; j++){

			puzzle[i][j] = v;
			v++;
		}		
		
		do{
			for (i = 0; i < N; i++)						/* randomly selected array components are switched */
			for (j = 0; j < N; j++){					

				v = rand()%(N-1);	k = rand()%(N-1);

				temp = puzzle[i][j];
				puzzle[i][j] = puzzle[v][k];
				puzzle[v][k] = temp;
			}

		} while (is_possible(puzzle) == 0);				/* If randomized puzzle is not solveable the it will get randomized until it is solveable */

}

/*---------------------------------------------------------------------------------------------*/

int is_possible(int puzzle [][N]){

	int i,j,count=0;

		for (i = 0; i < (N-1); i++)						/* By calculating inversion finding out if the puzzle is solveable */
		for (j = (i+1); j < N; j++){

			if(puzzle[j][i] != 0 && puzzle[i][j] != 0 && puzzle[j][i]>puzzle[i][j])
				count++;
		}

		if (N%2)
			if(count%2) return 1; 						/* According to parities of N and inversion the puzzle is accepted as solveable*/
			else		return 0;
		else
			if(count%2) return 0; 						
			else		return 1;

}

/*---------------------------------------------------------------------------------------------*/

void print_array(int puzzle [][N]){

	int i,j,v,f;

	printf("\n   **");	v=1;

		for (i = 0; i < N; i++){						/* Loops to print the puzzle in a desired form */

			printf(" %2d *",v);	v++;
		}
		
		printf("\n"); v=1;

		for (f = 0; f < 5+5*N; f++)
			printf("*");	printf("\n");	
		for (f = 0; f < 5+5*N; f++)
			printf("*");	printf("\n");

		

		for (i = 0; i < N; i++){
			
			printf("%2d **",v); v++;
			
			for (j = 0; j < N; j++){
				
				if (puzzle[i][j] == 0)					/* Instead of 0, blank is printed */
					printf("    *");
				else
					printf(" %2d *",puzzle[i][j]);

			}
			printf("\n");

			for (f = 0; f < 5+5*N; f++)
				printf("*");	

			printf("\n");
		}
	printf("\n");
}

/*---------------------------------------------------------------------------------------------*/

enum directions{down=2, left=4, right=6, up=8};	/* Using numpad with these values makes inputting less confusing */

void swap(int puzzle [][N]){

	int row, column, direct, err=0, i, j, r0, c0, temp;

	do{

		printf("row: ");		scanf("%d",&row);					/* Asking for inputs to modify the puzzle and keep asking for them until valid ones recieved */
		printf("column: ");		scanf("%d",&column);
		printf("direction (2 for down, 4 for left, 6 for right, 8 for up): ");	scanf("%d",&direct);
	
		if (row<1 || row>N || column<1 || column>N || (direct != down && direct != left && direct != right && direct != up)){

			printf("\nPlease check your entries.\n\n");	print_array(puzzle); err=1;	/* If invalid entry is detected this message printed */
	}
		else err=0;

	} while (err == 1);


	for (i = 0; i < N; i++)				/* Position of 0 (blank) is assigned to "r0" and "c0" */
	for (j = 0; j < N; j++){

		if (puzzle[i][j] == 0){

			r0=i+1;	c0=j+1;				/* +1 is because of first row and column of the array starts with 0 but printed as 1 */
		}			
	}

	if ( row == r0 || column == c0 )	/* The component that will be modified needs to be in same column or row as 0 (blank) */
	{
		switch(direct){					/* "Switch", modifies the puzzle according to the direction got by user */

			case down:

			if(row < r0){
				j = r0-row;				/* j is used to store how many times the swap will be executed */
				for (i = 0; i < j; ++i){					

					temp = puzzle[r0-1][c0-1];					/* With the help of "temp" values in array compenents that are adjacent to 0 (blank), are switched with 0 one by one (once if it is enough) */
					puzzle[r0-1][c0-1] = puzzle[r0-2][c0-1];	
					puzzle[r0-2][c0-1] = temp;
					r0--;
				}
			}
			else printf("\nImpossible move.\n");	break;		/* If the move is not possible this message is printed */


			case left:											/* Similar procedure when direction is left */

			if(column > c0){
				j = column-c0;
				for (i = 0; i < j; ++i){

					temp = puzzle[r0-1][c0];
					puzzle[r0-1][c0] = puzzle[r0-1][c0-1];
					puzzle[r0-1][c0-1] = temp;
					c0++;
				}
			}
			else printf("\nImpossible move.\n");	break;


			case right:											/* Similar procedure when direction is right */

			if(column < c0){
				j = c0-column;
				for (i = 0; i < j; ++i){

					temp = puzzle[r0-1][c0-1];
					puzzle[r0-1][c0-1] = puzzle[r0-1][c0-2];
					puzzle[r0-1][c0-2] = temp;
					c0--;
				}
			}
			else printf("\nImpossible move.\n");	break;


			case up:											/* Similar procedure when direction is up */

			if(row > r0){
				j = row-r0;
				for (i = 0; i < j; ++i){

					temp = puzzle[r0][c0-1];
					puzzle[r0][c0-1] = puzzle[r0-1][c0-1];
					puzzle[r0-1][c0-1] = temp;
					r0++;
				}
			}
			else printf("\nImpossible move.\n");

			break;
		}


	}
	else printf("\nImpossible move.\n");

}

/*---------------------------------------------------------------------------------------------*/

void done(int puzzle [][N], int *completed){

	int i,j,v=1,flag=0;

		for (i = 0; i < N; i++)							/* From puzzle[0][0] to puzzle[N-1][N-1] components are checked if they are in ascending order */
		for (j = 0; j < N; j++){

			if((puzzle[i][j] == v || puzzle[i][j] == 0) && flag == 0){

				if 	(puzzle[i][j] == 0) v=v;			/* 0 is skipped since it is the blank */
				else {
					v++; *completed=1;					/* If it is completed then "completed" is assignned as 1 and loop at line 17 is stopped */
				}
			}
			else {*completed = 0; flag = 1;}
			}
}