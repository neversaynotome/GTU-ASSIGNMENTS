#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
	char *country, *capital;
	int population;
	bool driving_side;
}data;

void menu(void);
void new_data(data **pointer, int count);				//gets input
void to_file(FILE *fptr, data **pointer, int count);	//writes to a file
void from_file(FILE *fptr, data **filepointer, int count);	//reads from a file
void data_printer(data **pointer, int count);				//prints the read data

void main(void)
{
	menu();		// menu function coordinates all of the operations
	
}


void menu(void){

	int operation, counter = 0;
	data *s = NULL, *s_file = NULL;
	FILE *ptr;
	ptr= fopen ("data.txt", "w+");

do
{
	printf("\n1-Enter New record\n");
	printf("2-Write to the file\n");
	printf("3-Read from the file\n");
	printf("4-Print the linked list\n");
	printf("5-EXIT\n");
	printf("Select operation: "); scanf("%d",&operation); printf("\n");	// switch case coordinates operations

	switch (operation){

		case 1:
			new_data(&s,counter);
			counter++;
		break;

		case 2:
			to_file(ptr,&s,counter);
		break;

		case 3:
			//s_file = (data*) malloc(sizeof(data)*(counter));	rewind(ptr);
			//from_file(ptr, &s_file, counter);
		break;

		case 4:
			data_printer(&s,counter);
		break;

		case 5:
			printf("//Terminated.//\n");
		break;

		default:
			printf("//Invalid input.//\n");
		break;
	}

} while (operation != 5);

fclose(ptr);
}



void new_data(data **pointer, int count){

	int i, population, side; char *country = malloc(100*sizeof(char)), *capital = malloc(100*sizeof(char));
	printf("Name of the country:"); scanf("%s",country);
	printf("Capital of the country:"); scanf("%s",capital);					// variables initialized and read from user
	printf("Population of %s:",country); scanf("%d",&population);
	printf("Do population of %s drive on right (Yes:1) (No:0):",country); scanf("%d",&side);

	if (*pointer == NULL){
		*pointer = (data*) malloc(sizeof(data));			// if array has no members

		(*pointer)->country = malloc(sizeof(country));
		strcpy((*pointer)->country,country);

		(*pointer)->capital = malloc(sizeof(capital));
		strcpy((*pointer)->capital,capital);

		(*pointer)->population = population;

		(*pointer)->driving_side = side;
	}
	else{
		data *temp = *pointer;								// if array has members already they are copied
		*pointer = (data*) malloc(sizeof(data)*(count+1));

		for (i = 0; i < count; ++i){
			(*pointer)[i].country = malloc(sizeof(temp[i].country));
			strcpy((*pointer)[i].country,temp[i].country);

			(*pointer)[i].capital = malloc(sizeof(temp[i].capital));
			strcpy((*pointer)[i].capital,temp[i].capital);

			(*pointer)[i].population = temp[i].population;

			(*pointer)[i].driving_side = temp[i].driving_side;
			
		}

		(*pointer)[count].country = malloc(sizeof(country));
		strcpy((*pointer)[count].country,country);

		(*pointer)[count].capital = malloc(sizeof(capital));
		strcpy((*pointer)[count].capital,capital);

		(*pointer)[count].population = population;

		(*pointer)[count].driving_side = side;
		
			free(temp);
		
	}
}



void to_file(FILE *fptr, data **pointer, int count){

	int i;

	for (i = 0; i < count; ++i){				// prints to a file one by one
	
	fprintf(fptr,"%s ",(*pointer)[i].country);
	fprintf(fptr,"%s ",(*pointer)[i].capital);
	fprintf(fptr,"%d ",(*pointer)[i].population);
	if ((*pointer)[i].driving_side) fprintf(fptr,"Right\n"); else fprintf(fptr,"Left\n");
	}
}


void from_file(FILE *fptr, data **filepointer, int count){

	int i, population; char *country = malloc(100*sizeof(char)), *capital = malloc(100*sizeof(char)), *side = malloc(6*sizeof(char));

	for (i = 0; i < count; ++i){
	
	fscanf(fptr,"%s",country);		// reads and stores the data to a new array one by one
	fscanf(fptr,"%s",capital);
	fscanf(fptr,"%d",&population);
	fscanf(fptr,"%s",side);
	}
}


void data_printer(data **pointer, int count){

	int i;

	for (i = 0; i < count; ++i){		// prints the data to terminal
	printf("%s\n",(*pointer)[i].country);
	}
}