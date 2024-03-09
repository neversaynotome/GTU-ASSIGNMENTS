/*
** hw5_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.02.23.55
** 
*/

#include <stdio.h>
#include <math.h>
#include "hw5_lib.h"


void operate_polynomials  (double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0, char op)
{
	double m6, m5, m4, m3, m2, m1, m0;

	switch (op) {

		case '+' :			/* According to operator, operations are made */

			*a3 += *b3; *a2 += *b2; *a1 += *b1; *a0 += *b0;

		break;

		case '-' :

			*a3 -= *b3; *a2 -= *b2; *a1 -= *b1; *a0 -= *b0;

		break;

		case '*' :
			m6 = ((*a3)*(*b3));													

			m5 = ((*a3)*(*b2)) + ((*a2)*(*b3));									

			m4 = ((*a3)*(*b1)) + ((*a2)*(*b2)) + ((*a1)*(*b3));					

			m3 = ((*a3)*(*b0)) + ((*a2)*(*b1)) + ((*a1)*(*b2)) + ((*a0)*(*b3));	

			m2 = ((*a2)*(*b0)) + ((*a1)*(*b1)) + ((*a0)*(*b2));					

			m1 = ((*a1)*(*b0)) + ((*a0)*(*b1));									

			m0 = ((*a0)*(*b0));													

			(*a3) = m6; (*a2) = m5; (*a1) = m4; (*a0) = m3; (*b3) = m2; (*b2) = m1; (*b1) = m0;
		break;
	}
}

/*------------------------------------------------------------------------------------------------*/

void four_d_vectors (double* mean_a0, double* mean_a1, double* mean_a2, double* mean_a3, double* longest_distance, int N)
{
	double m0=0, m1=0, m2=0, m3=0, d0, d1, d2, d3, t0, t1, t2, t3, euclidian_distance;	int i;

for (i = 0; i < N; ++i)									/* "t" variables will store temporary values to calculate longest distance */
{														/* "d" variables will be used to store inputs */
														/* "m" variables will store the sum of vectoral values to calculate the avarage */
	t0 = d0; t1 = d1; t2 = d2; t3 = d3;
	printf("enter %d. 4d vector: ",i+1);
	scanf("%lf %lf %lf %lf", &d0, &d1, &d2, &d3);

	
		
	m0 += d0; m1 += d1; m2 += d2; m3 += d3;

	if (i>0) distance_between_4d_points ((d0 - t0), (d1 - t1), (d2 - t2), (d3 - t3), &euclidian_distance);	/* calling with the difference of 2 consecutive inputs */

	


}

*mean_a0 = m0/N; *mean_a1 = m1/N; *mean_a2 = m2/N; *mean_a3 = m3/N;	(*longest_distance) = euclidian_distance;	/* Necessary assingments before printing */

}


void distance_between_4d_points (double d0, double d1, double d2, double d3, double* euclidian_distance)
{
	double max_dist=0;

	max_dist = d0*d0 + d1*d1 + d2*d2 + d3*d3;	/* euclidian_distance is calculated */

	if ( max_dist > (*euclidian_distance)) (*euclidian_distance) = sqrt(max_dist);	/* if the recent distance is the bigger one it will overwrite the older one */


}

/*------------------------------------------------------------------------------------------------*/

void dhondt_method (int* partyA, int* partyB, int* partyC, int* partyD, int* partyE, int numberOfSeats)
{
	int A=1, B=1, C=1, D=1, E=1, numA, numB, numC, numD, numE, max_vote=0, check=0, i;


	printf("Enter votes of Party A: ");	scanf("%d",&numA);		/* asking for votes */
	printf("Enter votes of Party B: ");	scanf("%d",&numB);
	printf("Enter votes of Party C: ");	scanf("%d",&numC);
	printf("Enter votes of Party D: ");	scanf("%d",&numD);
	printf("Enter votes of Party E: ");	scanf("%d",&numE);
	printf("Enter number of seats: ");	scanf("%d",&numberOfSeats);

	for (i = 0; i < numberOfSeats ; ++i)
	{																						
		max_vote = max(max(max(max((numA/A), (numB/B)), (numC/C)), (numD/D)), (numE/E));	/* This line compares all of the votes then finds out the maximum one by the help of function "max" (see line 123) */
		
		if 		((numA/A) == max_vote)	{ A++;  (*partyA)++; }		/* if a party has the biggest number of votes it will get a seat*/
		else if ((numB/B) == max_vote)	{ B++;	(*partyB)++; }
		else if ((numC/C) == max_vote)	{ C++;  (*partyC)++; }
		else if ((numD/D) == max_vote)	{ D++;  (*partyD)++; }
		else if ((numE/E) == max_vote)	{ E++;  (*partyE)++; }

	}
}

int max(int a, int b){	/* returns the bigger value */

	if (a>b) return a; 
	else 	 return b;
}

/*------------------------------------------------------------------------------------------------*/

void order_2d_points_cc (double* x1, double* y1, double* x2, double* y2, double* x3, double* y3)
{
	int m1, m2, m3, tx, ty, point1, point2, point3;

	/* I underestimated how much time this part was going to take so unfortunately i didn't finish it */

	/*
	if ((*y2)==0 && (*x2)>=0) { tx = (*x2); 	ty = (*y2); 
								(*x2) =	(*x1); 	(*y2) = (*y1);		
								(*x1) = tx; 	(*y1) = ty;   }
	if ((*y3)==0 && (*x3)>=0) { tx = (*x3); 	ty = (*y3); (*x3) =	(*x1); 	(*y3) = (*y1);	(*x1) = tx; (*y1) = ty;   }

	if ((*y1)>0 && (*x1)!=0) m1 = (*y1)/(*x1);	if ((*y2)>0 && (*x2)!=0) m1 = (*y2)/(*x2);	if ((*y3)>0 && (*x3)!=0) m1 = (*y3)/(*x3);
	if (m1>0)


	if ((*y1)==0 && (*x1)>=0) point1 = 1;	if ((*y2)==0 && (*x2)>=0) point2 = 1;	if ((*y3)==0 && (*x3)>=0) point3 = 1;

	if ((*y1)>0 && (*x1)!=0) m1 = (*y1)/(*x1);	if ((*y2)>0 && (*x2)!=0) m1 = (*y2)/(*x2);	if ((*y3)>0 && (*x3)!=0) m1 = (*y3)/(*x3);


	if ((*y1)==0 && (*x1)>=0) point1 = 1;	if ((*y2)==0 && (*x2)>=0) point2 = 1;	if ((*y3)==0 && (*x3)>=0) point3 = 1;

	if ((*y1)>0 && (*x1)!=0) m1 = (*y1)/(*x1);	if ((*y2)>0 && (*x2)!=0) m1 = (*y2)/(*x2);	if ((*y3)>0 && (*x3)!=0) m1 = (*y3)/(*x3);


	if ((*y1)==0 && (*x1)>=0) point1 = 1;	if ((*y2)==0 && (*x2)>=0) point2 = 1;	if ((*y3)==0 && (*x3)>=0) point3 = 1;

	if ((*y1)>0 && (*x1)!=0) m1 = (*y1)/(*x1);	if ((*y2)>0 && (*x2)!=0) m1 = (*y2)/(*x2);	if ((*y3)>0 && (*x3)!=0) m1 = (*y3)/(*x3);
	*/
}

/*------------------------------------------------------------------------------------------------*/

void number_encrypt (unsigned char* number)
{
	char b7='-', b6='-', b5='-', b4='-', b3='-', b2='-', b1='-', b0='-';
	get_number_components (*number, &b7, &b6, &b5, &b4, &b3, &b2, &b1, &b0);
	reconstruct_components (number, b7, b6, b5, b4, b3, b2, b1, b0);
}


void get_number_components (unsigned char number, char* b7, char* b6, char* b5, char* b4, char* b3, char* b2, char* b1, char* b0)
{
	int i;

	
		if ((number%2) == 1)	{(*b0) = 1;	number /= 2;}	/* By using remainder of the division by 2 this algorithm figures binary version out of the input */
		else					{(*b0) = 0;	number /= 2;}	/* and assings results accordingly */

		if ((number%2) == 1)	{(*b1) = 1;	number /= 2;}
		else					{(*b1) = 0;	number /= 2;}

		if ((number%2) == 1)	{(*b2) = 1;	number /= 2;}
		else					{(*b2) = 0;	number /= 2;}

		if ((number%2) == 1)	{(*b3) = 1;	number /= 2;}
		else					{(*b3) = 0;	number /= 2;}

		if ((number%2) == 1)	{(*b4) = 1;	number /= 2;}
		else					{(*b4) = 0;	number /= 2;}

		if ((number%2) == 1)	{(*b5) = 1;	number /= 2;}
		else					{(*b5) = 0;	number /= 2;}

		if ((number%2) == 1)	{(*b6) = 1;	number /= 2;}
		else					{(*b6) = 0;	number /= 2;}

		if ((number%2) == 1)	{(*b7) = 1;	number /= 2;}
		else					{(*b7) = 0;	number /= 2;}

	
}


void reconstruct_components (unsigned char* number, char b7, char b6, char b5, char b4, char b3, char b2, char b1, char b0)
{
		char temp;	int i=0;				/* it is possible to go straight to last bit order but i decided to go with this conventional method */

		temp = b7;	b7 = b2;	b2 = temp;	/* With the help of a temporary variable this algorithm will swap bits according to the task */
		temp = b6;	b6 = b3;	b3 = temp;
		temp = b5;	b5 = b0;	b0 = temp;
		temp = b4;	b4 = b1;	b1 = temp;

while(i != 2){								/* circular shift executed 2 times */
	i++;
		temp = b7;	b7 = b0;	b0 = temp;
		temp = b6;	b6 = b7;	b7 = temp;
		temp = b5;	b5 = b6;	b6 = temp;
		temp = b4;	b4 = b5;	b5 = temp;
		temp = b3;	b3 = b4;	b4 = temp;
		temp = b2;	b2 = b3;	b3 = temp;
		temp = b1;	b1 = b2;	b2 = temp;
		temp = b0;	b0 = b1;	b1 = temp;
}


*number = 128*b7 + 64*b6 + 32*b5 + 16*b4 + 8*b3 + 4*b2 + 2*b1 + b0;	/* after the swaps calculating the new number */

}
