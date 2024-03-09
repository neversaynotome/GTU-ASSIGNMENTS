/*
** main.c:
**
** The test/driver program for the homework.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.02.23.55
** 
*/


#include <stdio.h>
#include "hw5_lib.h"


void test_operate_polynomials () 
{
	double a3,a2,a1,a0,b3,b2,b1,b0,cof;	int i;	char op, degree;

	printf("Inputs for the first polynomial please: ");	scanf("(%c, %lf)",&degree,&cof);	

	for (i = 0; i < 4; ++i)
	{

		switch (degree) {																/* by using "(%c, %lf)" in scanf, degree helps us identify where to assign the coefficients */

			case '3':	a3 = cof;	break;
			case '2':	a2 = cof;	break;
			case '1':	a1 = cof;	break;
			case '0':	a0 = cof;	break;
			default	:	printf("Incorrect input.\n");	break;
		}
		scanf(", (%c, %lf)",&degree,&cof);												/* after first coefficient this scanf reads inputs */
	}

	printf("\nInputs for the second polynomial please: "); scanf("%*c(%c, %lf)",&degree,&cof);

	for (i = 0; i < 4; ++i)																/* Same procedures for 2nd polynomial */
	{

		switch (degree) {

			case '3':	b3 = cof;	break;
			case '2':	b2 = cof;	break;
			case '1':	b1 = cof;	break;
			case '0':	b0 = cof;	break;
			default	:	printf("Incorrect input.\n");	break;
		}
		scanf(", (%c, %lf)",&degree,&cof);
	}

	printf("Enter the operator: ");	scanf(" %c",&op);

	operate_polynomials(&a3, &a2, &a1, &a0, &b3, &b2, &b1, &b0, op);

	switch (op) {																		/* After sending the inputs printing out outputs according to operator */

		case '+':	printf("Resulted Coefficients: %f, %f, %f, %f\n",a3,a2,a1,a0 );	break;
		case '-':	printf("Resulted Coefficients: %f, %f, %f, %f\n",a3,a2,a1,a0 );	break;
		case '*':	printf("Resulted Coefficients: %f, %f, %f, %f, %f, %f, %f\n",a3,a2,a1,a0,b3,b2,b1);	break;
	}
}


void test_four_d_vectors ()
{
	double mean_a0=0.0, mean_a1=0.0, mean_a2=0.0, mean_a3=0.0, longest_distance=0.0;
	int N=5;
	four_d_vectors (&mean_a0, &mean_a1, &mean_a2, &mean_a3, &longest_distance, N);
	printf("Mean a0: %f\nMean a1: %f\nMean a2: %f\nMean a3: %f\nThe longest distance between two points: %f\n\n\n", mean_a0, mean_a1, mean_a2, mean_a3, longest_distance);
}


void test_dhondt_method ()
{
	int partyA=0, partyB=0, partyC=0, partyD=0, partyE=0, numberOfSeats=0;
	dhondt_method (&partyA, &partyB, &partyC, &partyD, &partyE, numberOfSeats);
	printf("Party A: %d seat(s).\nParty B: %d seat(s).\nParty C: %d seat(s).\nParty D: %d seat(s).\nParty E: %d seat(s).\n\n\n", partyA, partyB, partyC, partyD, partyE);
}


void test_order_2d_points_cc ()
{
	double x1=1.0, y1=2.0, x2=2.0, y2=3.0, x3=3.0, y3=4.0;
	order_2d_points_cc (&x1, &y1, &x2, &y2, &x3, &y3);
	printf("Counter-Clockwise Order: (%f,%f) - (%f,%f) - (%f,%f)\n\n\n", x1, y1, x2, y2, x3, y3);
}


void test_number_encrypt ()
{
	unsigned char number=125;
	number_encrypt (&number);
	printf("Encrypted number: %d\n\n\n", number);
}


/*
** main function for testing the functions...
**
*/
int main(void) {
	
	test_operate_polynomials ();
	test_four_d_vectors ();
	test_dhondt_method ();
	test_order_2d_points_cc ();
	test_number_encrypt ();
	
	return (0);
} /* end main */
