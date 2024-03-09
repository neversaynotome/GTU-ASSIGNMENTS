#include <stdio.h>
#include <math.h>


void poly(void);									/* Declaring the functions */

void parm(void);

void prime(void);


int main(void){										/* Calling the functions respectively */

	poly();

	parm();

	prime();

	return 0;
}

/*------------------------------------------------------------------------*/

void poly(void){

	int degree;												/* "degree" will store the degree of the polynomial, "cof" will be used to print coefficient(s) of the polynomial */
	double cof;

printf("\nPlease enter the degree of the polynomial: "); scanf("%d",&degree);	/* Asking for inputs */

printf("\nPlease enter coefficients of the polynomial: "); scanf("%lf",&cof);

printf("\nP(x) = ");

while (degree != 0){											/* To print coefficients of polynomial until "x^0"s coefficient */

	if (degree > 1 && cof != 0)

		if (cof >= 0.95 && cof <= 1.04999)						/* If coefficient is "1" or "-1" (or it is going to be printed as rounded to aforementioned values) */
			printf("x^%d ",degree);								/* function won't print the coefficient(s) */

		else if (cof <= -0.95 && cof >= -1.04999)				
			printf("-x^%d ",degree);

		else													/* if not function will print the coefficient too */
			printf("%.1fx^%d ",cof,degree);


	else if (degree == 1 && cof != 0)							/* Same precedure as line 38's "if else" block but for (x) */

		if (cof >= 0.95 && cof <= 1.04999)
			printf("x ");

		else if (cof <= -0.95 && cof >= -1.04999)
			printf("-x ");

		else
			printf("%.1fx ",cof);

	scanf("%lf",&cof);											/* This "scanf" works with "while" at line 36 to print the coefficients respectively */

	if ( cof>0 )												/* If the coefficient is positive, function will print "+" */
		printf("+");

degree--;

}

if (cof != 0)													/* Last coefficient is printed right away if it is not "0" */
	printf("%.1f",cof);

printf("\n\n");
}

/*------------------------------------------------------------------------*/

void parm(void){

	int  err=0, num, tnum, temp, i, numsize=0, tempsize, sum=0, reverse=0, arm=0, pal=0;
	char c;		/* "c" and "err" for error checking; "num", "tnum" and "temp" will store the input; "i" will be used in "for" loop */
do 				/* "numsize" and "tempsize" will store digit number of the input; "sum" will store sum of the cubes of the input */
{				/* "reverse" will store reversed version of the input, "arm" and "pal" are used to decide if the input is an armstrong and/or a palindrome number */
	if (err>0)
		printf("Please check your input.\n\n");

	printf("Please enter the number: ");  scanf("%d",&num);  c=getchar();

	printf("\n");
	err++;

} while (num<0 || c != '\n');									/* Asking for the input until a "valid" one is recieved */

tnum = num;

while (tnum>0)													/* This function will store digit number of the input in "numsize" (ex. 4 for "6028") */
{
    tnum /= 10;

    numsize++;
}

tempsize = numsize; temp = num; tnum = num;						/* Necessary assingnment are made for function to functions properly */

for (i = 0; i < numsize; ++i)									/* This loop will decide if the input is an armstrong and/or a palindrome number */
{

	temp = temp%10;												/* "temp" stores last digit of the input (ex. 7 for "127") */

	reverse += temp*pow(10,tempsize-1);							/* "temp" is multiplied with 10^[(digit number)-1] (ex. "temp" stores 7 so "reverse" will store 7*10^(3-1)=700) */

	sum += temp*temp*temp;										/* "sum" stores cube of the digit ("temp") */

	temp = (tnum-temp)/10;										/* The processed digit is extracted from input (ex 127-7 = 120) then the result is divided with 10 (120/10 = 12) */

	tnum = temp;												/* (since "temp" will be processed, "tnum" stores the value in "temp") */

	tempsize--;

}

if (sum == num)	arm++;											/* line 122 and 123 processes values provided by the "for" loop to print desired output */
if (reverse == num) pal++;

if 			(arm==1 && pal==1)	printf("The number is an armstrong and a palindrome number.\n\n");
else if 	(arm==1 && pal==0)	printf("The number is only an armstrong number.\n\n");
else if 	(arm==0 && pal==1)	printf("The number is only a palindrome number.\n\n");
else							printf("The number is neither an armstrong nor a palindrome number.\n\n");

}

/*------------------------------------------------------------------------*/

void prime(void){

	int err=0, num1, num2, i, k, prime, sum=0;
	char c;		/* "c" and "err" are for error checking, "num1" and "num2" will store input values, "i" and "k" will be used in "for" loops */
				/* "prime" will be used to decide if the processed number is a prime number, "sum" will store sum of the prime numbers */
do
{
	if (err>0)
		printf("Please check your entries.\n\n");

	printf("Please enter the first number: "); scanf("%d",&num1); c=getchar();

	printf("Please enter the second number: "); scanf("%d",&num2); c=getchar();

	printf("\n");
	err++;

} while (num1<=0 || num2<=0 || c != '\n' || num1>=num2);		/* Asking for input until desired input is scanned */

printf("Sum of the prime numbers between %d and %d: ",num1, num2);

for (i = ++num1; i < num2; ++i)									/* Deciding if the number that is processed is prime number or not */
{
	prime=1;
	for (k = 2; k <= i/2; ++k)									
		if (i%k == 0) prime=0;

	if (prime == 1)
		sum += i;												/* Sums prime numbers and stores it in "sum" */

}

printf("%d\n",sum);												/* Printing out "sum" */

}