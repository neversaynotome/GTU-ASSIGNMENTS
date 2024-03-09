#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct synonym{							/* "usernames.txt", "synonyms.txt" and "antonyms.txt" are required to be in the same */
	char *word;									/* directory with the source code for the functionality of this C program.  */
	char **synonyms;							/* Keep in mind that words with spaces are not processable by this program (requires minimum modifications but doesn't have them :D ) */
	int count;
	struct synonym *next;						/* An explanation for the text files: word antonym1 antonym2 antonym3 antoym4... */
}synonym;

typedef struct antonym{
	char *word;
	char **antonyms;
	int count;
	struct antonym *next;
}antonym;

void menu();										/* Oversees everything, contains the menu. */
void username(char*);								/* Processes and oversees user's files. */
void reader(synonym**, antonym**, int*, int*);		/* Reads the data from text files and stores to linked lists (it created). */
char** twod_char(char**, char*, int*);				/* Creates and edits 2D char arrays of linked list nodes dynamically (ex. char** antonyms;) */
void question_picker(synonym**, antonym**, char*, int*, int*, int*, int*);/* Picks (considering .bin files) a question to ask, edits linked lists (wrong answer) if user asks to */
int data_read(char*, char, int, int);				/* Checks data in .bin file and helps picking the suited */
void data_store(char*, char, int, int);				/* Stores the necesseary data to .bin file */
void editor(synonym**, antonym**);					/* If user wants to add a word directly to linked lists executes necessary operation */
void re_write(synonym**, antonym**);				/* Re-writes the text files with the updated data in linked lists */

void main(void){

	menu();											/* Calls "menu" */
	printf("\nTerminated.\n");
}

/*-------------------------------------------------------*/

void menu(){

	char uname[50];										/* "uname" contains name of the user. */
	printf("Enter an username: "); scanf("%s",uname);
	username(uname);									/* "username" called for operations regarding .bin files */

	int input = 0, s_count = 0, a_count = 0, squestion_count = 0, aquestion_count = 0;	/* "count"s store the number of words in text files */
																						/* "question_count"s store number of asked questions */
	synonym *slist = NULL; antonym *alist = NULL;										/* pointers for linked lists */

	reader(&slist, &alist, &s_count, &a_count);											/* Linked lists are created */

	while (input != 3){
		printf("\n/////////////////////\n");
		printf("\n1-Solve a question\n2-Add a word\n3-Exit\n\nSelect an operation: "); scanf("%d",&input); printf("\n/////////////////////\n");

		switch (input){

			case 1:
				question_picker(&slist, &alist, uname, &s_count, &a_count, &squestion_count, &aquestion_count);	/* User will get a question to answer */
			break;

			case 2:
				editor(&slist, &alist);		/* Adding an antonym or synonym to the texts (eventually with the function "re_write") */
			break;

			case 3:
				
			break;

			default:
				printf("\nInvalid entry.\n");
			break;
		}
	}
	re_write(&slist, &alist); /* Updating text files */
}

/*-------------------------------------------------------*/

void username(char* name){

	int flag = 1; char compare[50];							/* "compare" will contain already existing usernames */

	FILE *cmp, *create; cmp = fopen("usernames.txt","r+");
	while (!feof(cmp)){										/* If user exists already then no need to create .bin file */
		fscanf(cmp,"%[^\n]%*c",compare);
  	if (strcmp(compare, name) == 0) flag = 0;
	}

	if (flag){fprintf(cmp,"%s\n",name); strcat(name,".bin"); create = fopen(name,"wb+"); fclose(create);}	/* Creates the .bin file if necessary */
	else strcat(name,".bin");
	fclose(cmp);
}

/*-------------------------------------------------------*/

void reader(synonym** sLL, antonym** aLL, int* scount, int* acount){

	char buffer[2000];

	FILE *sptr, *aptr;	sptr = fopen("synonyms.txt","r");	aptr = fopen("antonyms.txt","r");

	if (sptr == NULL || aptr == NULL){
		printf("Unable to open the files.\n"); exit(1);
	}

	if((*sLL) == NULL){										/* If there is no existing nodes first one is created. */
		(*sLL) = (synonym*) malloc(sizeof(synonym*));

		fscanf(sptr,"%s",buffer);
		(*sLL)->word = (char *) malloc(strlen(buffer)+1);
			strcpy((*sLL)->word, buffer);

		fscanf(sptr," %[^\n]%*c",buffer);
		(*sLL)->synonyms = twod_char((*sLL)->synonyms, buffer, &((*sLL)->count)); /* (in this case) synonyms are stored to the 2D array by the function "twod_char" */

		(*sLL)->next = NULL; *scount+=1;
	}

	synonym *stmp = (*sLL);									/* If there is an existing node(s) new ones will be added next to them */

	while(!feof(sptr)){
		stmp->next = (synonym*) malloc(sizeof(synonym*)); stmp = stmp->next;

		fscanf(sptr,"%s",buffer);
		stmp->word = (char *) malloc(strlen(buffer)+1);
			strcpy(stmp->word, buffer);

		fscanf(sptr," %[^\n]%*c",buffer);
		stmp->synonyms = twod_char(stmp->synonyms, buffer, &(stmp->count));

		stmp->next = NULL; *scount+=1;
	}

	if((*aLL) == NULL){										/* Same operations for "antonym" linked list */
		(*aLL) = (antonym*) malloc(sizeof(antonym*));

		fscanf(aptr,"%s",buffer);
		(*aLL)->word = (char *) malloc(strlen(buffer)+1);
			strcpy((*aLL)->word, buffer);

		fscanf(aptr," %[^\n]%*c",buffer);
		(*aLL)->antonyms = twod_char((*aLL)->antonyms, buffer, &((*aLL)->count));

		(*aLL)->next = NULL; *acount+=1;
	}

	antonym *atmp = (*aLL);

	while(!feof(aptr)){
		atmp->next = (antonym*) malloc(sizeof(antonym*)); atmp = atmp->next;

		fscanf(aptr,"%s",buffer);
		atmp->word = (char *) malloc(strlen(buffer)+1);
			strcpy(atmp->word, buffer);

		fscanf(aptr," %[^\n]%*c",buffer);
		atmp->antonyms = twod_char(atmp->antonyms, buffer, &(atmp->count));

		atmp->next = NULL; *acount+=1;
	}
}

/*-------------------------------------------------------*/

char** twod_char(char** words, char* buffer, int* count){

	char *temp = strtok(buffer, " "); int i = 0;	/* The word is read, rest of the row (ex. antonyms) will be processed by strtok since they have spaces in between */

		words = (char**) malloc(sizeof(char*));		/* First word is added to the dynamic 2d array */
		*words = (char*) malloc(strlen(temp)+1);
		strcpy(*words, temp);

		temp = strtok(NULL, " ");

	while(temp != NULL){							/* rest is handled */
		i++;
		words = (char**) realloc(words, (i+1)*sizeof(char*));
		words[i] = (char*) malloc(strlen(temp)+1);
		strcpy(words[i], temp);
		temp = strtok(NULL, " ");
	}

	(*count) = i+1;
	return words;
}

/*-------------------------------------------------------*/

void question_picker(synonym** sLL, antonym** aLL, char* uname, int* scount, int* acount, int* sq, int* aq){

	srand(time(NULL));
	
	int i, flag = 0, a_or_s, to_ask, wordnum = 0, redraw = 0, edit; char answer[200];	/* "a_or_s" contains the type of the question */
	synonym *stmp = (*sLL); antonym *atmp = (*aLL);										/* "to_ask" is the number of the word (or node), "wordnum" helps with movement from and to nodes */
																						/* "redraw" helps with the deciding the type of question */
	a_or_s = rand()%2;	if ((*sq) > (*aq))	a_or_s = 1;			/* After randomly choosing a question type the "if" here helps with balancing type of questions */

	if (a_or_s == 0){ 						/* 0 for synonym, 1 for antonym */
		(*sq)+=1;

		while(redraw == 0){					/* redraw is assigned 1 if word is good to ask */
			to_ask = rand()%(*scount);
			if((*sq) != 1 && (*aq) != 1) redraw = data_read(uname, 's', ((*sq) + (*aq)), to_ask);	/* data_read decides if "to_ask" is suitable to ask */
			else redraw = 1;
		}

		while(wordnum < to_ask){			/* "to_ask" (which contains number of the eligible node) helps to iterate to the desired node (or word) */
			stmp = stmp->next; wordnum+=1;
		}
		printf("\nEnter a synonym for the word \"%s\": ",stmp->word); scanf(" %s",answer);	/* Finally question is asked */

		for (i = 0; i < stmp->count; ++i){						/* Answer is compared with the exiting words */
			if(strcmp(stmp->synonyms[i],answer) == 0) flag++;
		}

		if (flag > 0)	data_store(uname, 's', wordnum, 1);		/* If answer is correct */
		else			data_store(uname, 's', wordnum, 0);

		if (flag > 0) printf("\nCorrect answer!\n");
		else{
			printf("\nYour answer for the word \"%s\" is not correct.\n\nWould you like to add it as a new synonym?\n\nNo (0) Yes (1): ",stmp->word);
			scanf("%d",&edit);
		}																					/* User is asked if word should be added to text files */
		if (edit == 1){
			stmp->synonyms = (char**) realloc(stmp->synonyms, (stmp->count)*sizeof(char*));
			stmp->synonyms[(stmp->count)] = (char*) malloc(strlen(answer)+1);
			strcpy(stmp->synonyms[(stmp->count)], answer); stmp->count+=1;
			printf("\nThe word has been added.\n");
		}
	}

	if (a_or_s == 1){ 											/* Same operations for antonyms */
		(*aq)+=1;

		while(redraw == 0){
			to_ask = rand()%(*acount);
			if((*sq) != 1 && (*aq) != 1) redraw = data_read(uname, 'a', ((*sq) + (*aq)), to_ask);
			else redraw = 1;
		}

		while(wordnum < to_ask){
			atmp = atmp->next; wordnum+=1;
		}
		printf("\nEnter an antonym for the word \"%s\": ",atmp->word); scanf(" %s",answer);

		for (i = 0; i < atmp->count; ++i){
			if(strcmp(atmp->antonyms[i],answer) == 0) flag++;
		}

		if (flag > 0)	data_store(uname, 'a', wordnum, 1);
		else			data_store(uname, 'a', wordnum, 0);

		if (flag > 0) printf("\nCorrect answer!\n");
		else{
			printf("\nYour answer for the word \"%s\" is not correct.\n\nWould you like to add it as a new antonym?\n\nNo (0) Yes (1): ",atmp->word);
			scanf("%d",&edit);
		}
		if (edit == 1){
			atmp->antonyms = (char**) realloc(atmp->antonyms, (atmp->count)*sizeof(char*));
			atmp->antonyms[(atmp->count)] = (char*) malloc(strlen(answer)+1);
			strcpy(atmp->antonyms[(atmp->count)], answer); atmp->count+=1;
			printf("\nThe word has been added.\n");
		}
	}
}

/*-------------------------------------------------------*/

int data_read(char* file, char s_or_a, int asked, int qnumber){

	FILE *binptr;	binptr = fopen(file,"rb+");

	int i = 0, ask = 0, answer, wordnum; char syn_ant;	/* "ask" contains a point that is proportional with its askability (according to PDF) */

	while (!feof(binptr)){ i++;							/* The "for" loop checks existing entries and calculates the askability of the word */
		fread(&syn_ant, sizeof(char), 1, binptr);
		fread(&wordnum, sizeof(int), 1, binptr);
		fread(&answer, sizeof(int), 1, binptr);

		if (syn_ant == s_or_a)							/* ex. if question is for a synonym then answer given to an antonym are ignored */
		if(qnumber == wordnum) 							/* If selected word is already asked and the answer is correct it gets less likely to asked (ask--;) */
			if (answer == 1) 	ask--;
			else				ask++;					/* if it is answered incorrectly then it gets more likely to get asked */
	}
	
	if (ask >= 0) 	return 1;
	else			return 0;

	fclose(binptr);
}

/*-------------------------------------------------------*/

void data_store(char* file, char s_or_a, int qnumber, int answer){

	FILE *binptr;	binptr = fopen(file,"rb+"); fseek(binptr, 0, SEEK_END);

	fwrite(&s_or_a, sizeof(char), 1, binptr);		/* Stores the data to .bin files by suitable output means */
	fwrite(&qnumber, sizeof(int), 1, binptr);
	fwrite(&answer, sizeof(int), 1, binptr);

	fclose(binptr);
}

/*-------------------------------------------------------*/

void editor(synonym** sLL, antonym** aLL){

	int input, flag = 0; char buffer[100], new[100]; synonym *stmp = (*sLL); antonym *atmp = (*aLL);

	printf("\nDo you want to add a(n) synonym (0) or antonym (1): "); scanf("%d",&input);

	switch(input){

		case 0: printf("\nEnter the word: "); scanf(" %s",buffer);

		while(stmp != NULL){											/* which word is wanted to have a new (in this case) synonym is asked */
			if(strcmp(stmp->word, buffer) == 0){ flag++;				/* If word exists then word to be add is asked */
				printf("\nWhich word do you want to add as a synonym to \"%s\": ",buffer); scanf(" %s",new);
				stmp->synonyms = (char**) realloc(stmp->synonyms, (stmp->count)*sizeof(char*));
				stmp->synonyms[(stmp->count)] = (char*) malloc(strlen(new)+1);
				strcpy(stmp->synonyms[(stmp->count)], new); stmp->count+=1;
			}
			stmp = stmp->next;
		}
		if (flag == 0){													/* If the word doesn't exist */
			printf("\nWord \"%s\" does not exist.\n",buffer);
		}
		else printf("\nWord added succesfully.\n");

		break;

		case 1: printf("\nEnter the word: "); scanf(" %s",buffer);

		while(atmp != NULL){											/* Same operations if word to be add is an antonym */
			if(strcmp(atmp->word, buffer) == 0){ flag++;
				printf("\nWhich word do you want to add as an antonym to \"%s\": ",buffer); scanf(" %s",new);
				atmp->antonyms = (char**) realloc(atmp->antonyms, (atmp->count)*sizeof(char*));
				atmp->antonyms[(atmp->count)] = (char*) malloc(strlen(new)+1);
				strcpy(atmp->antonyms[(atmp->count)], new); atmp->count+=1;
			}
			atmp = atmp->next;
		}
		if (flag == 0){
			printf("\nWord \"%s\" does not exist.\n",buffer);
		}
		else printf("\nWord added succesfully.\n");

		break;

		default:
			printf("\nIncorrect input.\n");
		break;

	}

}

/*-------------------------------------------------------*/

void re_write(synonym** sLL, antonym** aLL){

	int i; FILE *sptr, *aptr;	sptr = fopen("synonyms.txt","w");	aptr = fopen("antonyms.txt","w");

	if (sptr == NULL || aptr == NULL){
		printf("Unable to open the file(s) to write to.\n"); exit(1);
	}

	synonym *stmp = (*sLL);

	while(stmp != NULL){						/* The text file contains synonyms are modified in a specific way to keep them only 'updated' w/out changing anything else */
		fprintf(sptr, "%s ",stmp->word);
		for (i = 0; i < stmp->count; ++i){
			fprintf(sptr, "%s",stmp->synonyms[i]);
			if (i+1 < stmp->count) fprintf(sptr, " ");
		}
		stmp = stmp->next;
		if(stmp != NULL) fprintf(sptr, "\n");
	}

	antonym *atmp = (*aLL);

	while(atmp != NULL){						/* Same operation for the text file that contains antonyms */
		fprintf(aptr, "%s ",atmp->word);
		for (i = 0; i < atmp->count; ++i){
			fprintf(aptr, "%s",atmp->antonyms[i]);
			if (i+1 < atmp->count) fprintf(aptr, " ");
		}
		atmp = atmp->next;
		if(atmp != NULL) fprintf(aptr, "\n");
	}

	fclose(sptr); fclose(aptr);

	printf("\nText files updated.\n");
}