#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fix_spelling_error(FILE *ptr_TEXT, FILE *ptr_DICT);			/* Functions are passed FILE pointers */
void fix_spelling_error2(FILE *ptr_TEXT, FILE *ptr_DICT);
char* find_best_correction(FILE *ptr_DICT, char *text, int num_err);/* text is the word gotten from text.txt and num_err is number of errors */

void main(void){

	FILE *ptr_TEXT, *ptr_DICT;

	ptr_TEXT = fopen("text.txt","r+");				/* FILE pointers declared */
	ptr_DICT = fopen("dictionary.txt","r");

	if(!ptr_TEXT || !ptr_DICT){						/* If it is not able to declare FILE then it exits the program */
   		printf("Something went wrong, terminating...\n");
   		exit(1);
	}

	fix_spelling_error(ptr_TEXT, ptr_DICT);
	//fix_spelling_error2(ptr_TEXT, ptr_DICT)	/* if words have 2 errors then this function can be called to fix errors */

	printf("Corrections have been made.\n");

	fclose(ptr_TEXT);	fclose(ptr_DICT); 
}

/*-----------------------------------------------------------------------------------------------*/

void fix_spelling_error(FILE *ptr_TEXT, FILE *ptr_DICT){

	char read, text[50];

	while(!feof(ptr_TEXT)){
		memset(text, 0, 50);								/* Clearing the text array to get new words wout problems */
		do{
			fscanf(ptr_TEXT,"%c",&read);					/* text is scanned char by char and if it is a alphabetic character it is passed to text array*/
			if (( read >= 'A' && read <= 'Z' ) || ( read >= 'a' && read <= 'z' ) && !feof(ptr_TEXT))
				strncat(text, &read, 1);

		} while (read != 32 && !feof(ptr_TEXT));

		if ( strlen(text)>1 ){

		find_best_correction(ptr_DICT, text, 1);	/* text contains the word with it and number of error the function is called */

	if (strcmp(text,"!!!") !=0 && !feof(ptr_TEXT)){	
		fseek(ptr_TEXT, -1*strlen(text)-1, SEEK_CUR);	/* function modifies text array itself and it is printed to appropiate place */
		fprintf(ptr_TEXT,"%s",text);
	}
	else if (strcmp(text,"!!!") !=0){					/* if cursor in text.txt at the end of file fseek is modified */
		fseek(ptr_TEXT, -1*strlen(text), SEEK_CUR);
		fprintf(ptr_TEXT,"%s",text);
	}
	}
	}
}

/*-----------------------------------------------------------------------------------------------*/

char* find_best_correction(FILE *ptr_DICT, char *text, int num_err){

	char dict[50], elig[3][50]; int found=0, i, j, eligible, correct, error, prior, vowel[3], v, check;

	fseek(ptr_DICT, 0, SEEK_SET);

	correct=0;	
	while(!feof(ptr_DICT)){
	
		fscanf(ptr_DICT,"%s",dict);		/* scanning words from dictionary.txt */

		if (strcmp(text,dict) == 0 && strlen(dict) == strlen(text)) correct++;	/* comparing text and dict if dictionary has the text itself it won't be processed */
	}

	fseek(ptr_DICT, 0, SEEK_SET);

	while(!feof(ptr_DICT)){
	
		fscanf(ptr_DICT,"%s",dict);

		if ( strlen(dict) == strlen(text) && correct == 0){	/* if edit distance is 1 and text and dict are same length dict is considered as eligible */
			eligible=0; 
			for (i = 0; i < strlen(text); ++i){
				if (dict[i] == text[i])	eligible++;
			}

			if (eligible == strlen(text)-num_err){
				check=0;
				for (i = 0; i < 3; ++i){					/* storing eligible word to an array */
					if (strcmp(dict,elig[i]) == 0) check++;
				}
				if (check == 0 && found<3){
					strcpy(elig[found], dict);	found++;
				}
			}
		}
	}

	v = 0;	error=0;
	if (found>0){											/* found stores number of eligible words */
	for (i = 0; i < found; ++i){
		prior=0;
		for (j = 0; j < strlen(text); ++j){

		if (elig[i][j] != text[j])	error=j;

		if (elig[i][error] == 'a' || elig[i][error] == 'e' || elig[i][error] == 'i' ||	/* if eligible words have more vowel they get prioritized */
            elig[i][error] == 'o' || elig[i][error] == 'u' || elig[i][error] == 'A' ||
            elig[i][error] == 'E' || elig[i][error] == 'I' || elig[i][error] == 'O' ||
            elig[i][error] == 'U'){

			prior++;
		}
		}

		if (prior == num_err || prior == 1){
			vowel[v] = i;	v++;	
		}
	}
	if(v == 0 && (found == 2 || found == 3)) 	strcpy(text,elig[1]);					/* text is modified according to pdf */
	if(v == 0 && found == 1) 					strcpy(text,elig[0]);
	if(v == 1)									strcpy(text,elig[vowel[0]]);
	if(v == 2 || v == 3)						strcpy(text,elig[vowel[1]]);
	}
	else strcpy(text,"!!!");
}

/*-----------------------------------------------------------------------------------------------*/

void fix_spelling_error2(FILE *ptr_TEXT, FILE *ptr_DICT){

	char read, text[50];

	while(!feof(ptr_TEXT)){													/* sam stuff is happening except for words that have 2 errors*/
		memset(text, 0, 50);
		do{
			fscanf(ptr_TEXT,"%c",&read);
			if (( read >= 'A' && read <= 'Z' ) || ( read >= 'a' && read <= 'z' ) && !feof(ptr_TEXT))
				strncat(text, &read, 1);

		} while (read != 32 && !feof(ptr_TEXT));

		if ( strlen(text)>2 ){

		find_best_correction(ptr_DICT, text, 2);

	if (strcmp(text,"!!!") !=0 && !feof(ptr_TEXT)){	
		fseek(ptr_TEXT, -1*strlen(text)-1, SEEK_CUR);
		fprintf(ptr_TEXT,"%s",text);
	}
	else if (strcmp(text,"!!!") !=0){	
		fseek(ptr_TEXT, -1*strlen(text), SEEK_CUR);
		fprintf(ptr_TEXT,"%s",text);
	}
	}
	}
}