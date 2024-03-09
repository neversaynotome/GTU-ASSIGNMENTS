#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{												/* I didn't have enough time to complete this HW so it is half-done */
	char *name;
	int genre, year;
	double budget, score;
}Movie;

int rows(FILE*);											/* counts row number in the text to figure out max. number of movies */
void order_finder(int*, FILE*);								/* according to first row figures out how to scan info */
int reader(int*, Movie*, char**, int*, FILE*);				/* reads the information from text file */
void ops(Movie*, int);											/* according to inputs executes necessary operations */

void main(){

	char *txt = malloc(30*sizeof(char));				/* name of the text file is got from student */

	FILE *fptr; printf("Enter the name of the text file: "); scanf("%s",txt);

	fptr = fopen(txt,"r");

	if(!fptr){						/* If it is not able to declare FILE pointer then it exits the program */
   		printf("Something went wrong, terminating...\n");
   		exit(1);
	}

	int r_num;														/* functions called respectively */

	r_num = rows(fptr); rewind(fptr);

	int *order = (int*) malloc(5);

	order_finder(order,fptr);

	Movie *movies = (Movie*) calloc(r_num,sizeof(Movie));

	char ** genres; int * genre_indexes, genre_counter;

	genre_counter = reader(order, movies, genres, genre_indexes, fptr);

	fclose(fptr);

	ops(movies, r_num);

printf("\n");
}

/*------------------------------------------------------------------*/

int rows(FILE* ptr){

	int count=0; char c;

	while(!feof(ptr)){
	fscanf(ptr,"%c",&c); if(c == '\n') count++;
	}
	return count;

}

/*------------------------------------------------------------------*/

void order_finder(int* arr,FILE* ptr){

	char *tmp = (char *) malloc(10*sizeof(char)); int k=0;

	while(k<5){
		fscanf(ptr," %[^,\n]%*c",tmp); 		
		if (strncmp(tmp,"budget",3)==0) arr[k]=0;
		if (strncmp(tmp,"score",3)==0) 	arr[k]=1;
		if (strncmp(tmp,"year",3)==0) 	arr[k]=2;
		if (strncmp(tmp,"name",3)==0) 	arr[k]=3;
		if (strncmp(tmp,"genre",3)==0)  arr[k]=4;
		k++;
	}
	free(tmp);
}

/*------------------------------------------------------------------*/

int reader(int* ordr,Movie* strt_arr,char** gnrs,int* gnr_indx, FILE* ptr){

	int count=0, movie_count=0, gnr_count=0; char *tmp, *garbage;

	while(!feof(ptr)){
		tmp = (char *) malloc(100*sizeof(char));
		fscanf(ptr," %[^,\n]%*c",tmp);
	
		if (ordr[count%5] == 0) 
			if (strcmp(tmp,"unknown") == 0) strt_arr[movie_count].budget = -1;
			else strt_arr[movie_count].budget = strtod(tmp,&garbage); 
		if (ordr[count%5] == 1) strt_arr[movie_count].score = strtod(tmp,&garbage);
		if (ordr[count%5] == 2) strt_arr[movie_count].year = (int)strtod(tmp,&garbage);
		if (ordr[count%5] == 3){ 
			strt_arr[movie_count].name = (char *)calloc(strlen(tmp) + 1, sizeof(char));
			strcpy(strt_arr[movie_count].name, tmp); }
		/*if (ordr[count%5] == 4){
			*gnrs = malloc(gnr_count+1 * sizeof(char *));
			gnrs[gnr_count] = (char *)malloc(strlen(tmp)+1);			didn't have time for this
			strcpy(gnrs[gnr_count], tmp); gnr_count++;
		}*/
		count++; if (ordr[count%5] == 0) movie_count++;
		free(tmp); //printf("%d\n",count );
	}

	return gnr_count;
}

/*------------------------------------------------------------------*/

void ops(Movie* array,int count){

	int input=0,i; double sum=0;

	while(input != 8){

	printf("1. List of the Sorted Data\n2. List of the Genres\n3. List of the Movie Through the Years\n4. List of the Movie Through the Scores\n5. All Informations of a Single Movie\n6. Avarage of the IMDB Scores\n7. Frequence of the Genres\n8. Exit\n\nPlease Select an operation: ");
	scanf("%d",&input);
	
	if (input == 6)										/* only prints average score partially */
	{
		for (i = 0; i < count-1; ++i)
		{
			sum+=array[i].score;
		}
		printf("\nThe average is: %.1f\n\n",sum/count-1 );
	}
	else printf("\nUNIMPLEMENTED\n\n");
}
}