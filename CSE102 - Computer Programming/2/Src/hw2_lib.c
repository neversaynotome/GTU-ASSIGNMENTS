/*
** hw2_lib.c:
**
** The source file implementing library functions.
**
*/

#include <stdio.h>
#include "hw2_lib.h"
#include <math.h>

int find_weekday_of_data(int day, int month, int year)
{
int dayno,wd;

if (month==1 || month ==2)																		/* using zeller's algorithm to find required info*/
wd = day+(2.6*(month+10)-0.2)-2*(year/100)+((year-1)%100)+((year/100)/4)+(((year-1)%100)/4);
else
wd = day+(2.6*(month-2)-0.2)-2*(year/100)+(year%100)+((year/100)/4)+((year%100)/4);

if(wd<0)
dayno = wd+6;
else
dayno = wd%7;

if (dayno!=0)
    return dayno;
else
	return 7;
}


int count_day_between_dates(int start_day, int start_month, int start_year, int end_day, int end_month, int end_year)
{
	int y,m,numdays=0;

	if(end_year-start_year>1)														/* (for different years) first we calculate the whole years and directly add it to returned value */
	{
		numdays = (end_year-start_year-1)*365.25;
		start_year=end_year-1;
	}

	
	if (end_year-start_year==1)														/* whole years are out of the way, for the "not whole year" couunting days one by one */
	{
		for (m = start_month; m < 13; ++m)
		{
			if (m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12){
			numdays=numdays+31;
			}

		else if (m==4 || m==6 || m==9 || m==11){
			numdays=numdays+30;
		}
		
		else{
			numdays=numdays+28;
		}
		}

		for (m = 1; m < end_month; ++m)
		{
			if (m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12){
			numdays=numdays+31;
			}

		else if (m==4 || m==6 || m==9 || m==11){
			numdays=numdays+30;
		}
		
		else{
			numdays=numdays+28;
		}
		}
		return numdays+end_day-start_day;
	}

	else{																		/* (no year difference) if both years are same this algorithm is used  */
		numdays=numdays-start_day+end_day;
		for (m = start_month; m < end_month; ++m)								/* counting days one by one but one "for" loop is enough here */
		{
			if (m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12)
			numdays=numdays+31;

		else if (m==4 || m==6 || m==9 || m==11)
			numdays=numdays+30;

		else
			numdays=numdays+28;
	}
return numdays;
	}
}



double find_angle(double a, double b, double c)
{
	double x,y,alpha;															
	if (a<=0 || b<=0 || c<=0)													/* error checking */
		printf("check your entries\n");

																				/* using Apollonius’s theorem to calculate length of the medians */
	x=sqrt(2*a*a+2*c*c-b*b)/3;													/* to create smaller triangle that contains "alpha" [(BGC) triangle] */
	y=sqrt(2*a*a+2*b*b-c*c)/3;
	alpha=acos((x*x+y*y-a*a)/(2*x*y));											/* finally knowing sides of the smaller triangle, equation consisting arccos gives us the value of alpha*/
    return alpha;
}


void print_tabulated(unsigned int r11, double r12, int r13, 
                     unsigned int r21, double r22, int r23, 
                     unsigned int r31, double r32, int r33, char border)
{
	int i;

	printf("┌");													/* by printing corner we are starting to create table */
	for (i = 0; i < 66; ++i)
    printf("%c",border);											/* printing borders */
	printf("┐\n|");

	for (i = 0; i < 6; ++i)											/* first row */
    printf(" ");
	printf("Row 101");
	for (i = 0; i < 6; ++i)
    printf(" ");
	printf("|");
	for (i = 0; i < 6; ++i)
    printf(" ");
	printf("Row ABCDEFG");
	for (i = 0; i < 6; ++i)
    printf(" ");
	printf("|");
	for (i = 0; i < 6; ++i)
    printf(" ");
	printf("Row XYZ123");
	for (i = 0; i < 6; ++i)
    printf(" ");
	printf("|\n|");

	for (i = 0; i < 66; ++i)										/* printing border */
    printf("%c",border);
	printf("|\n|");

if(r11>=0 && r11 <100){												/* second row */
	printf("%10d",r11 );
	for (i = 0; i < 9; ++i)											/* checking to see how big first column integers are we print " "s (space) accordingly to print them centered */
    printf(" ");
	}
else if(r11>=100 && r11 <10000){
	printf("%11d",r11 );
	for (i = 0; i < 8; ++i)
    printf(" ");
	}
else{
	printf("%12d",r11 );
	for (i = 0; i < 7; ++i)
    printf(" ");
	}
	printf("|");
	printf("%-18g",r12 );
	for (i = 0; i < 5; ++i)
    printf(" ");
	printf("|");
	printf("%-18d",r13 );
	for (i = 0; i < 4; ++i)
    printf(" ");
	
	printf("|\n|");													/* printing border */
	for (i = 0; i < 66; ++i)
    printf("%c",border);
	printf("|\n|");

if(r21>=0 && r21 <100){												/* third row */
	printf("%10d",r21 );
	for (i = 0; i < 9; ++i)
    printf(" ");
	}
else if(r21>=100 && r21 <10000){
	printf("%11d",r21 );
	for (i = 0; i < 8; ++i)
    printf(" ");
	}
else{
	printf("%12d",r21 );
	for (i = 0; i < 7; ++i)
    printf(" ");
	}
	printf("|");
	printf("%-18g",r22 );
	for (i = 0; i < 5; ++i)
    printf(" ");
	printf("|");
	printf("%-18d",r23 );
	for (i = 0; i < 4; ++i)
    printf(" ");

	printf("|\n|");
	for (i = 0; i < 66; ++i)
    printf("%c",border);
	printf("|\n|");

if(r31>=0 && r31 <100){												/* fourth row */
	printf("%10d",r31 );
	for (i = 0; i < 9; ++i)
    printf(" ");
	}
else if(r31>=100 && r31 <10000){
	printf("%11d",r31 );
	for (i = 0; i < 8; ++i)
    printf(" ");
	}
else{
	printf("%12d",r31 );
	for (i = 0; i < 7; ++i)
    printf(" ");
	}
	printf("|");
	printf("%-18g",r32 );
	for (i = 0; i < 5; ++i)
    printf(" ");
	printf("|");
	printf("%-18d",r33 );
	for (i = 0; i < 4; ++i)
    printf(" ");
	printf("|\n└");
	for (i = 0; i < 66; ++i)
    printf("%c",border);
	printf("┘\n");

}