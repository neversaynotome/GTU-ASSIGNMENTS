#include <stdio.h>
#include <math.h>													/* "-lm" is required to run the code without errors */

void calculate_fibonacci_sequence();

void decide_perfect_harmonic_number();

void difference_max_min();

void bmi_calculation();


int main(){															/* The main function */

	calculate_fibonacci_sequence();									/* Calling the functions one by one */
	
	decide_perfect_harmonic_number();

	difference_max_min();
	
	bmi_calculation();
}

/*------------------------------------------------------------*/

void calculate_fibonacci_sequence(){								/* Prints fibonacci sequence numbers to the term number given by the user */

	int term,fibo,temp1,temp2,i;									/* "term" will contain term number, "fibo", "temp1", "temp2" and "i" will be used to print fibonacci sequence numbers */
	char c;															/* "c" will be used to store non integer inputs for error checking */

	do{

	printf("Please enter term(s) number: ");						/* Assigning input to "term" or (if input is non-integer) to "c" */
	scanf("%d",&term);
	c=getchar();

while ((term <= 0 || c != '\n' )&& c != '*')						/* Error checking, if input is not a positive integer then function will ask for the appropiate input until the wanted input is acquired */
{
	while ( term <= 0 && c == '\n'){								/* If input is a negative integer the function will ask for "positive" one */

		printf("\nPlease enter “positive” term(s) number: ");
		scanf("%d",&term);
		c=getchar();
	}

	while ( c != '\n' && c != '*'){									/* If input is non-integer the function will ask for a "numeric" input */

		printf("\nPlease enter “numeric” term(s) number: ");
		scanf("%d",&term);
		c=getchar();
	}
}

if (c != '*'){														/* If we finally get a desired input (positive integer or '*') then function will skip error checking and start printing the sequence */
	
printf("\nFibonacci Sequence: \n\n");								/* If '*' is entered function will just end without printing the fibonacci sequence */

fibo=1,temp1=1,temp2=0;												/* Everytime function is going to print the sequence the used variables will be set to their functional values */

for (i = 0; i < term; ++i){											/* Basic operation of printing fibonacci sequence happens here */

	printf("%d\n\n",fibo );
	fibo  = temp1+temp2;
	temp2 = temp1;
	temp1 = fibo;
}

printf("\n");

}

	} while (c != '*');												/* This "do while" condition will stop function asking for input after '*' is entered */

printf("\n");

}

/*------------------------------------------------------------*/

void decide_perfect_harmonic_number(){								/* Calculates and outputs if the acquired number is perfect and harmonic divisor number or not */

	int number,divider,count,perfect;								/* "number" will be used to store acquired value, "divider" will be used in "for" loop to acquire divisors of the input */
	double harmonic;												/* "count" will be used to store divisor number, "perfect" will be used to calculate if the "number" is perfect number or not */
	char c;															/* "harmonic" will be used to decide if the number is a harmonic divider number or not, "c" will be used to end the function and error checking */

do{

perfect=1,harmonic=1,count=1;										/* Variables are assigned to their functional values everytime calculation happens */

printf("\nPlease enter input number: ");							/* Acquiring then assigning the input to the "number" variable */
scanf("%d",&number);
c=getchar();

printf("\n");

if (number > 0 && c == '\n')										/* If input is a desired input then calculation will happen */
{

printf("Natural Number Divisors: 1");								/* Printing 1 right away to get more preferred output */
																	/* also because of line 99 the function assigns "perfect" to 1 and don't divide "number" with 1 since all integers will be divided full by 1*/
	for (divider = 2; divider <= number; ++divider){				/* "number" will be divided to all integers smaller than it (including itself, excluding 1) */

		if (number%divider==0){										/* if division is a full one, divider will be printed */
		
			count++;

			harmonic += divider;									/* "harmonic" stores sum of the all full dividers */

			printf(", %d",divider);

		if (divider != number)										/* All full divisors (excluding "number" itself) are stored in "perfect" */

			perfect += divider;
		}
	}

	if (number == 1)												/* Inıtially "perfect" is assigned 1 assuming every integer will be fully divided by 1 but if input is 1 we need to re assign it to 0 */
	perfect--;														/* the reason for this adjustment is the definition, only full divider 1 has is itself so assumption fails only when input is 1 */

	printf("\n\nIs Perfect Number?: ");								/* If sum of all full divisors (excluding "number" itself) is equal to "number" then it is a perfect number */

	if (perfect == number)
		printf("Yes\n");

	else
		printf("No\n");



	printf("\nIs Harmonic Divisor Number?: ");						/* Using "count" (number of full divisors), "harmonic" (sum of full divisors) and "number" to decide if acquired input is harmonic divisor number or not*/

	if (fmod(count/(harmonic/number),1)==0)
		printf("Yes\n");

	else
		printf("No\n");
}

else if (!(c == '*'))												/* If "getchar" command reads an undesired input then function outputs an error message */
	printf("Your input is incorrect.\n");

} while (c != '*');													/* If "getchar" command reads '*' as an input then function ends */

printf("\n");

}

/*------------------------------------------------------------*/

void difference_max_min(){											/* Prints maximum, minimum and difference between maximum and minimum numbers among 5 acquired integer values */

	int number,i,max=-2147483648,min=+2147483647;					/* "number" will be used to store acquired value, "max" will be used to store found maximum value, "min" will be used to store found minimum value */
																	/* "max" and "min" stores maximum and minimum values an "int" value type can store respectively to make comparisons without any problems */
	printf("Please enter 5 numbers: \n\n");							

	for (i = 0; i < 5; ++i){										/* "for" loop will run 5 times to acquire 5 inputs, "i" is used to run the loop for 5 times */

	scanf("%d",&number);

	if (number > max)												/* Comparing current "max" and "min" if comparison is valid we assign "number" to "max" or "min" accordingly */
		max = number;												/* First input will overwrite both "max" and "min" because of their initial values */

	if (number < min)
		min = number;
	}

	printf("\nMaximum number is: %d\n", max );						/* Printing maximum, minimum and the difference between */

	printf("\nMinimum number is: %d\n", min );

	printf("\nDifference between maximum and minimum is: %d\n\n\n", max-min );
}

/*------------------------------------------------------------*/

void bmi_calculation(){												/* Calculates BMI then prints the category according to calculated BMI value */

double w,h;															/* "w" will be used to store weight, "h" will be used to store height */

	printf("Please enter weight (in kg): ");						/* Acquiring necessery information to calculate BMI */
	scanf("%lf",&w);

	printf("Please enter height (in meters): ");
	scanf("%lf",&h);

	printf("Your category: ");

	if ( w/(h*h) < 16.0 )											/* According to calculated BMI value this if else block will print the category */
		printf("Severely Underweight\n");

	else if ( w/(h*h) >= 16.0  && w/(h*h) < 18.5 )
		printf("Underweight\n");

	else if ( w/(h*h) >= 18.5  && w/(h*h) < 25.0 )
		printf("Normal\n");

	else if ( w/(h*h) >= 25.0  && w/(h*h) < 30.0 )
		printf("Overweight\n");

	else if (w/(h*h) > 30.0 )
		printf("Obese\n");
}