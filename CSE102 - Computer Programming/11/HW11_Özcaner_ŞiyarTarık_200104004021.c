#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Movie_Budget{
	char *name;
	int budget, year;
	struct Movie_Budget *next;
}Movie_Budget;

typedef struct Movie_Name{
	char *name, *genre;
	double score;
	struct Movie_Name *next;
}Movie_Name;

void reader(Movie_Budget*, Movie_Name*, char**, FILE*);		/* reads the information from text file */
char** genre_list(char**, char*, int*);						/* creates a list of genres */
int name_comparer(Movie_Budget**, Movie_Name**, int, char*, char*, double, int);	/* if the film is already read updates the info */
void B_lister(Movie_Budget**, int, char*, int);				/* */
void N_lister(Movie_Name**, char*, char*, double);			/* */
void ops(Movie_Name**, Movie_Budget**,char** ,int);			/* according to inputs executes necessary operations */


void main(){

	char *txt = malloc(30*sizeof(char));				/* name of the text file is got from user */

	FILE *fptr; printf("Enter the name of the text file: "); scanf("%s",txt);

	fptr = fopen(txt,"r");

	if(!fptr){						/* If it is not able to declare FILE pointer then it exits the program */
   		printf("Something went wrong, terminating...\n");
   		exit(1);
	}

	Movie_Budget *mv_budget = NULL; Movie_Name *mv_name = NULL;	/* Linked list pointers are created */

	char ** genres; 
	char *garbage = (char *) malloc(100*sizeof(char)); fscanf(fptr," %[^\n]%*c",garbage); free(garbage); /* First line is discarded */

	reader(mv_budget, mv_name, genres, fptr);

	fclose(fptr);

}

/*------------------------------------------------------------------*/
void reader(Movie_Budget* Mbudget, Movie_Name* Mname, char** gnrs, FILE* ptr){

	int count=0, gnr_count=0; char *tmp, *garbage;

	int budget, year; char *name, *genre; double score;

	while(!feof(ptr)){
		tmp = (char *) malloc(100*sizeof(char));			/* "tmp" stores strings with the help of line 58 */
		fscanf(ptr," %[^,\n]%*c",tmp);						/* " %[^,\n]%*c" helps to store strings until ',' or '\n' */
		
		if (count%5 == 0) 									/* with the help of "count" algorithm stores 'budget', 'genre' etc. respectively */
			if (strcmp(tmp,"unknown") == 0) budget = -1;
			else budget = strtod(tmp,&garbage);

		if (count%5 == 1){
			genre = (char *) malloc(strlen(tmp)+1);
			strcpy(genre, tmp);
			
		}
		if (count%5 == 2){
			name = (char *) malloc(strlen(tmp)+1);
			strcpy(name, tmp);
		}

		if (count%5 == 3) score = strtod(tmp,&garbage);
		if (count%5 == 4) year = (int)strtod(tmp,&garbage);
		
		count++;

		if (count%5 == 0 && count > 0){						/* algorithm knows it has read a line when count%5 is 0 hence 5 piece of information */
															/* after reading every line, necessary functions are called to store the input */
			gnrs = genre_list(gnrs, genre, &gnr_count);		
			if (name_comparer(&Mbudget, &Mname, budget, genre, name, score, year) == 1 && count>5 ){
			B_lister(&Mbudget, budget, name, year);	
			N_lister(&Mname, genre, name, score);
			}
			else if (count == 5) {
				B_lister(&Mbudget, budget, name, year);
				N_lister(&Mname, genre, name, score);
			}
			}

		free(tmp);
	}

	ops(&Mname, &Mbudget, gnrs, gnr_count);					/* operations will be done with the linked lists and genre array (and counter) */

}

/*------------------------------------------------------------------*/

char** genre_list(char** gnrs, char* genre,int *gnr_count){

	int i = 0, flag = 0;

	if ((*gnr_count) == 0){ 							/* for first time gnrs is created and first genre is stored */
		gnrs = (char**) malloc(sizeof(char*));
		*gnrs = (char*) malloc(strlen(genre)+1);
		strcpy(*gnrs, genre); (*gnr_count)++;
	}
	else{
		while(i < (*gnr_count)){							/* later we need to chck if the genre exits already */
			if(strcmp(genre, gnrs[i]) == 0){flag=1; break;}
			i++;
		}

		if (flag == 0){															/* if it doesn't exits it is stored */
			gnrs = (char**) realloc(gnrs, ((*gnr_count)+1)*sizeof(char*));
			gnrs[(*gnr_count)] = (char*) malloc(strlen(genre)+1);
			strcpy(gnrs[(*gnr_count)], genre); (*gnr_count)++;
		}
	}

	return gnrs;
}

/*------------------------------------------------------------------*/

int name_comparer(Movie_Budget** Mbudget, Movie_Name** Mname, int budget, char* genre, char* name, double score, int year){

    Movie_Budget* currB = *Mbudget;
    Movie_Name* currN = *Mname;
    while(currB != NULL){

    if (strcmp(currB->name,name) == 0){			/* check if the movie is stored already */
        strcpy(currB->name,name);				/* if it exits than the information is updated */
        currB->budget = budget;
        currB->year = year;
        strcpy(currN->name,name);
        strcpy(currN->genre,genre);
        
        return 0;
    }
    currB = currB->next;
    currN = currN->next;
    }

    return 1;
}

/*------------------------------------------------------------------*/

void B_lister(Movie_Budget** Mbudget, int budget, char* name, int year){

	int counter = 0;
	
	Movie_Budget* tmp_B = (Movie_Budget*) malloc(sizeof(Movie_Budget*));
	Movie_Budget* prevB = NULL; Movie_Budget* currB = *Mbudget;

	if ((*Mbudget) == NULL){												/* if linked list is not initialized it is initialized and first member is created */
		(*Mbudget) = (Movie_Budget*) malloc(sizeof(Movie_Budget*));

		(*Mbudget)->name = (char *) malloc(strlen(name)+1);
			strcpy((*Mbudget)->name, name);
		(*Mbudget)->budget = budget;
		(*Mbudget)->year = year;
		(*Mbudget)->next = NULL;

		return;
	}

	tmp_B->name = (char *) malloc(strlen(name)+1);							/* new node that will be added to linked list is created */
				strcpy(tmp_B->name, name);
				tmp_B->budget = budget;
				tmp_B->year = year;
				tmp_B->next = NULL;
	
	while(currB->next != NULL){												/* in this while loop algorithm does two operations */
		
		if (year < currB->year){											/* here it looks for a appropiate place to ge into the list, it needs to have bigger year value */
			prevB = currB;													/* if node has a smaller year value it looks for next values */
			currB = currB->next; counter++;
		}
		
		else{																/* if no comparison is made then it means new node needs to be added at the top of the linked list */
			if (counter == 0){

				tmp_B->next = *Mbudget;
				*Mbudget = tmp_B;
				return;
			}
			else {															/* if not then it will be added in-between two nodes */

				prevB->next = tmp_B;
				tmp_B->next = currB;
				return;
			}
		}
	}
		currB->next = tmp_B;												/* if none of the operations above is performed it means new node will be added to bottom */
}



void N_lister(Movie_Name** Mname,  char* genre, char* name, double score){	/* same thing as "B_lister" goes here for "Movie_Name" linked list */

		int counter = 0;
	
	Movie_Name* tmp_N = (Movie_Name*) malloc(sizeof(Movie_Name*));
	Movie_Name* prevB = NULL; Movie_Name* currB = *Mname;

	if ((*Mname) == NULL){
		(*Mname) = (Movie_Name*) malloc(sizeof(Movie_Name*));

		(*Mname)->name = (char *) malloc(strlen(name)+1);
			strcpy((*Mname)->name, name);
		(*Mname)->genre = (char *) malloc(strlen(genre)+1);
		strcpy((*Mname)->genre, genre);
		(*Mname)->score = score;
		(*Mname)->next = NULL;

		return;
	}

	tmp_N->name = (char *) malloc(strlen(name)+1);
		strcpy(tmp_N->name, name);
	tmp_N->genre = (char *) malloc(strlen(genre)+1);
		strcpy(tmp_N->genre, genre);
	tmp_N->score = score;
	tmp_N->next = NULL;
	
	while(currB->next != NULL){												/* rather then year score is relevant here */
		
		if (score <= currB->score){
			prevB = currB;
			currB = currB->next; counter++;
		}
		
		else{

			if (counter == 0){

				tmp_N->next = *Mname;
				*Mname = tmp_N;

				return;
			}
			else {

				prevB->next = tmp_N;
				tmp_N->next = currB;

				return;
			}
		}
	}
		currB->next = tmp_N;

}

/*------------------------------------------------------------------*/
		
void ops(Movie_Name** Mname, Movie_Budget** Mbudget,char** genres ,int genre_counter){

	int input=0, i=0, count, print_count=0, year, choice, flag; double avrg, score; char* movie = (char*) malloc(100*sizeof(char));
	Movie_Name* name_print = NULL; Movie_Budget* budget_print = NULL;

	while(input != 8){

	printf("\n1. List of the Sorted Data\n2. List of the Genres\n3. List of the Movie Through the Years\n4. List of the Movie Through the Scores\n5. All Informations of a Single Movie\n6. Avarage of the IMDB Scores\n7. Frequence of the Genres\n8. Exit\n\nPlease Select an operation: ");
	scanf("%d",&input);

	switch (input){

		case 1:
			printf("\n///UNIMPLEMENTED///\n");						/* I didn't have time for this :c */
		break;

		case 2:
		name_print = (*Mname);
		for (i = 0; i < genre_counter; ++i)printf("%s\n",genres[i]);	/* genres are printed  */
		break;

		case 3:
			budget_print = (*Mbudget);									/* necessary values are asked */
			flag = 0;
			printf("Year: "); scanf("%d",&year);
			printf("Until (0) or Since (1): "); scanf("%d",&choice);
			if (choice == 0)											/* if "year" of movie is smaller then it is printed */
			{
				while(budget_print != NULL){
				if (budget_print->year < year){ printf("%s\n",budget_print->name); flag++;}
				budget_print = budget_print->next;	
				}
			}
			else if(choice == 1){										/* here it needs to have a bigger (or equal) year value to be printed */
				while(budget_print != NULL){
				if (budget_print->year >= year){ printf("%s\n",budget_print->name); flag++;}
				budget_print = budget_print->next;	
				}
			}
			else{ printf("\nInvalid input\n"); flag++;}

			if (flag == 0) printf("\nNo match found.\n");
		
		break;

		case 4:															/* nearly identical operations as "case 3" happens here for score */
			name_print = (*Mname);
			flag = 0;
			printf("Score: "); scanf("%lf",&score);
			printf("Until (0) or Since (1): "); scanf("%d",&choice);
			if (choice == 0)
			{
				while(name_print != NULL){
				if (name_print->score < score){ printf("%s %.1f\n",name_print->name,name_print->score); flag++;}
				name_print = name_print->next;	
				}
			}
			else if(choice == 1){
				while(name_print != NULL){
				if (name_print->score >= score){ printf("%s %.1f\n",name_print->name,name_print->score); flag++;}
				name_print = name_print->next;	
				}
			}
			else{ printf("\nInvalid input\n"); flag++;}

			if (flag == 0) printf("\nNo match found.\n");
		
		break;

		case 5:
		name_print = (*Mname);
		budget_print = (*Mbudget);
		flag = 0;

		printf("Movie Name: "); scanf(" %[^\n]%*c",movie);				/* name is asked */
		while(name_print != NULL){										/* linked lists are look for the name of the movie if it is found it is printed */
				if (strcmp(name_print->name,movie) == 0) { flag = 1;
					printf("\nName: %s\nGenre: %s\nscore: %.1f\n",name_print->name, name_print->genre, name_print->score);
			}
				name_print = name_print->next;
		}
		
		while(budget_print != NULL){									/* here the rest of the info is printed */
				if (strcmp(budget_print->name,movie) == 0) {
					if (budget_print->budget == -1) printf("Budget: unknown\nYear: %d\n",budget_print->year);
					else printf("Budget: %d\nYear: %d\n",budget_print->budget, budget_print->year);
				}
				budget_print = budget_print->next;
				}
			if (flag == 0) printf("No match found.\n");
		
		break;

		case 6:
			count = 0; avrg = 0;
			name_print = (*Mname);

			while(name_print != NULL){									/* scores in "Movie_Name" linked list are summed to calculate the average */
				avrg += name_print->score;
				count++;
				name_print = name_print->next;
				}
				printf("\nThe average: %.2f\n",avrg/count);
		break;

		case 7:															/* comparisons of genres made and counter is printed  */
		for (i = 0; i < genre_counter; ++i){
			printf("%-15s ",genres[i]);
			while(name_print != NULL){
				if (strcmp(name_print->genre,genres[i]) == 0) print_count++;
				name_print = name_print->next;
			}printf("%d\n",print_count);
			print_count=0; name_print = (*Mname);
		}

		break;

		case 8:
			printf("\n///TERMINATED///\n\n");
		break;

		default:
		printf("///Invalid input///\n");
		break;
	}
	
}
}