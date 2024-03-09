/*
** hw4_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.03.03.20.16
** 
*/

#include <stdio.h>
#include "hw1_lib.h"


double integral3(double a0, double a1, double a2, double a3, double xs, double xe, double delta)		/* this function does definite integration for a 3rd degree polynomial */
{

    	double x,total=0;											/* x is for value will be used in polynomial, total is used to store areas of rectangles */

    for (x=xs+delta/2; x<xe; x=x+delta){									/* starting calculation of areas from a half delta up from lower limit until */
    														/* x gets bigger than upper limit. */
		total= total+delta*(((a0*x+a1)*x+a2)*x+a3);							/* value of polynomial is multiplicated with delta and stored in total */
    }

    return total;												/* we are returning the value of areas of rectangles */
}


double integral4(double a0, double a1, double a2, double a3, double a4, double xs, double xe, double delta) /* same procedure as integral3 function but for a 4th degree polynomial */
{
	
    	double x,total=0;

    for (x=xs+delta/2; x<xe; x=x+delta){
    
		total= total+delta*((((a0*x+a1)*x+a2)*x+a3)*x+a4);
    }

    return total;
}


double root3(double a0, double a1, double a2, double a3, double xs, double xe)		/* this function calculates a root of 3rd degree polynomial */
{
    
    double x,value,root;									/* x is for value will be used in polynomial, value stores value of polynomial, root will be used */
    												/* to store found root */
for (x=xs; x<xe; x=x+0.000001){								/* "x" will be increased very little */

	value=(((a0*x+a1)*x+a2)*x+a3);							/* calculating polynomial with "x" value and storing it "value" variable */
	
	if (value<0.00001 && value>-0.00001){							/* entering if "value" (value of polynomial) very close to 0 */
												
		root=x;									/* the "x" is stored as "root" */
	}
}

    return root;										/* returning "root" */
}


double root4(double a0, double a1, double a2, double a3, double a4, double xs, double xe)	/* same procedure as root4 function but for 4th degree polynomial*/
{

    double x,value,root;									
    
for (x=xs; x<xe; x=x+0.000001){

	value=((((a0*x+a1)*x+a2)*x+a3)*x+a4);
	
	if (value<0.00001 && value>-0.00001){
		root=x;
	}
}

    return root;
}
