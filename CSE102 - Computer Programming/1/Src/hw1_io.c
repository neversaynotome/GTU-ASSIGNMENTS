/*
** hw1_io.c:
**
** The source file implementing output functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.03.03.20.16
** 
*/


#include <stdio.h>
#include "hw1_io.h"


void write_polynomial3(double a0, double a1, double a2, double a3)  		/* this function prints 3rd degree polynomial */
{
    printf("p(x) = ");								
	
	if(a0!=0){								/* checking the multiplier if it is 0 or not, if it is 0 we won't print that part. (x^3 for this particular part) */
		if(a0==1){							/* checking if multiplier is 1 if it is, no need to print the multiplier. (just prints x^3) */
			printf(" x^3");
		}
		else if(a0==-1){						/* checking if multiplier is -1 (if it is it will just print "-x^3" no need to print 1) */
			printf(" -x^3");
		}
		else								/* checking if multiplier is 1 (same thing with line 22 but for 1) */
		printf(" %.1fx^3",a0);
	}
	
	if(a1>0){								/* prints + if multiplier is positive */
	printf(" +");
	}
	
	if(a1!=0){								/* same things happen for all multipliers until line 66 */
		if(a1==1){
			printf(" x^2");
		}
		else if(a1==-1){
			printf(" -x^2");
		}
		else
		printf(" %.1fx^2",a1);
	}
	
	if(a2>0){
	printf(" +");
	}
	
	if(a2!=0){
		if(a2==1){
			printf(" x");
		}
		else if(a0==-1){
			printf(" -x^3");
		}
		else
		printf(" %.1fx",a2);
	}
	
	if(a3>0){								/* here we always going to print the multiplier unless it is 0 so no need to check if it is 1 or -1 */
	printf(" +");
	}
	
	if(a3!=0){
	printf(" %.1f\n",a3);
	}
}


void write_polynomial4(double a0, double a1, double a2, double a3, double a4) /* this function prints 4th degree polynomial */
{
    printf("p(x) = ");
	
	if(a0!=0){								/* same things happen here as "write_polynomial3" with the addition of an extra multiplier */
		if(a0==1){
			printf(" x^3");
		}
		else if(a0==-1){
			printf(" -x^3");
		}
		else
		printf(" %.1fx^3",a0);
	}
	
	if(a1>0){
	printf(" +");
	}
	
	if(a1!=0){
		if(a1==1){
			printf(" x^2");
		}
		else if(a0==-1){
			printf(" -x^3");
		}
		else
		printf(" %.1fx^2",a1);
	}
	
	if(a2>0){
	printf(" +");
	}
	
	if(a2!=0){
		if(a2==1){
			printf(" x");
		}
	else if(a0==-1){
			printf(" -x^3");
		}
		else
		printf(" %.1fx",a2);
	}
	
	if(a3>0){
	printf(" +");
	}
	
	if(a3!=0){
		if(a3==1){
			printf(" x");
		}
	else if(a0==-1){
			printf(" -x^3");
		}
		else
		printf(" %.1fx",a3);
	}
	
	if(a4>0){
	printf(" +");
	}
	
	if(a4!=0){
	printf(" %.1f\n",a4);
	}
}
