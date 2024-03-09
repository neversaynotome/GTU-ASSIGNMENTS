#include <stdio.h>
#include <string.h>
#define N 25	/* This algorithm can process N*15 customers so for N=25 it is able to process up to 375 customers */
				/* 5*N for 0, 3*N for 1 and 2 each, 2*N for 3 and 4 each */
typedef struct {
	char name [50];
	int age, label;
	
}credentials;

void sorter(int label, int cus_num[][15], int id);					/* Sorts customers according to their labels when new customer is queued */
void processer(credentials struct_arr[15*N], int cus_num[][15]);	/* Processes the customer first in the queue */

void main(){

	int i,j,p,input,numofcus=0,cus_id=0,sorted_ids[N][15];			/* "p" is used to print the sequence, "numofcus" stores number of customer that is processed */
	credentials crdt[15*N];											/* "cus_id" is given to customers and every customer have an exclusive one and */
																	/* "sorted_ids" are where "cus_id"s are stored according to labels of customers */
	for (i = 0; i < N ; ++i)
	for (j = 0; j < 15; ++j)		/* First of all elements of "sorted_ids" are assigned as -1 */
		sorted_ids[i][j] = -1;

	for (i = 0; i < 15*N ; ++i)		/* same for "label" elements of the of "credentials" struct */
		crdt[i].label = -1;

	printf("\n/////Banking system/////\n");

	do{
		printf("\n////////////////////////\n\nCurrent Sequence:");

		p=0;
		for (i = 0; i < N ; ++i)						/* Printing current sequence */
		for (j = 0; j < 15; ++j){
			if (sorted_ids[i][j] != -1 && numofcus > 0){		/* Since customer ids are stored in "sorted_ids" sorted it just prints labels ex. struct[id].label */
			printf("%d", crdt[ sorted_ids[i][j] ].label); p++;	/* p is used to print "-"s appropiately */
			if (numofcus != p){
				printf("-");
			}
			}
		}

		printf("\n\n////////////////////////\n\n1-Add customer\n\n2-Process customer\n\n3-Exit processing\n\nEnter an operation code: ");	scanf("%d",&input);

		switch (input){

			case 1:
				printf("\nPlease enter the name of the customer: ");scanf("%s", crdt[cus_id].name);
				printf("Please enter the age of the customer: ");	scanf("%d", &crdt[cus_id].age);
				printf("Please enter the label of the customer: ");	scanf("%d", &crdt[cus_id].label);

				if(crdt[cus_id].label >= 0 && crdt[cus_id].label <= 4){				/* If label is valid "sorter" is called */
					sorter(crdt[cus_id].label, sorted_ids, cus_id);
					numofcus++; cus_id++;											/* Tracking number of customers to process */
				}
				else 	printf("\n///Invalid label.///\n");
			break;

			case 2:
				if (numofcus == 0) printf("\n///Sequence is empty.///\n");
				else {processer(crdt, sorted_ids);	numofcus--;}				/* If there is a customer to process then "processer" is called */
			break;

			case 3: 	printf("\n///Terminated.///\n\n");
			break;

			default: 	printf("\n///Invalid code.///\n");
			break;
		}
		/*
		printf("\n");							*//* This piece of code can be used to print array of ids for a further demonstration of the algorithm *//*
		for (i = 0; i < 5 ; ++i){
		for (j = 0; j < 15; ++j)
		printf("%d ",sorted_ids[i][j]);
		printf("\n");
		}*/

	} while (input != 3);
}

void sorter(int label, int cus_num[][15], int id){
	
	int i,j;

	switch (label){						/* label of the most recent customer is sent to this function */

		case 0:
			for (i = 0; i < N; ++i)		/* The array that stores ids are in this shape "-1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1" */
			for (j = 0; j < 5; ++j){	/* 											   "-1 -1 -1 ..." 								  */
				if(cus_num[i][j]==-1){	/* so using the secondary index of this array we can put ids in accordance to their priority so sequence is printed accordingly */
					cus_num[i][j]=id;	/* this method allocates cus_num[][0] to cus_num[][4] for label 0 and so on, not the most efficient way but simplifies stuff a lot :D */
					j=5;i=N;			/* an example of "cus_num" or "sorted_ids": "12 13 14 -1 -1 0 2 3 -1 -1 -1 17 -1 19 -1" */
				}
			}
		break;

		case 1:
			for (i = 0; i < N; ++i)		/* indexes are set accordinly for rest of the labels */
			for (j = 5; j < 8; ++j){
				if(cus_num[i][j]==-1){ cus_num[i][j]=id; j=8; i=N;}
			}
		break;

		case 2:
			for (i = 0; i < N; ++i)
			for (j = 8; j < 11; ++j){
				if(cus_num[i][j]==-1){ cus_num[i][j]=id; j=11;i=N;}
			}
		break;

		case 3:
			for (i = 0; i < N; ++i)
			for (j = 11; j < 13; ++j){
				if(cus_num[i][j]==-1){ cus_num[i][j]=id; j=13;i=N;}
			}
		break;

		case 4:
			for (i = 0; i < N; ++i)
			for (j = 13; j < 15; ++j){
				if(cus_num[i][j]==-1){ cus_num[i][j]=id; j=15;i=N;}
			}
		break;
	}
}

void processer(credentials struct_arr[15*N], int cus_num[][15]){
	
	int i,j,to_process;

	for (i = 0; i < N ; ++i)			/* Searching for a non -1 number in "cus_num" array, first to found is to be processed */
	for (j = 0; j < 15; ++j){
		if(cus_num[i][j] != -1){
			printf("\n///Customer %s is processed///\n",struct_arr[cus_num[i][j]].name);
			to_process = struct_arr[cus_num[i][j]].label; i=N;j=15;}
	}

	switch (to_process){				/* "to_process" stores the label of the customer that is going to be processed */

		case 0:
			for (i = 0; i < N; ++i)
			for (j = 0; j < 5; ++j){
				if(struct_arr[ cus_num[i][j] ].label == 0){			/* Label of customers are checked by their ids and if the label is 0 algorithm processes the customer */
					struct_arr[ cus_num[i][j] ].label = -1;
					while(j<5){ cus_num[i][j] = cus_num[i][j+1]; j++;}	/* Arbitrary example of what "while" does to array of ids: 12 33 22 46, 33 22 46 46, */
					cus_num[i][4] = -1; j=5; i=N;							/* ("46" in the end needs to be emptied so) 33 22 46 -1 */
				}
			}
		break;

		case 1:							/* This shifting-like process is done for customers with other labels by the appropiate indexes */
			for (i = 0; i < N; ++i)
			for (j = 5; j < 8; ++j){
				if(struct_arr[ cus_num[i][j] ].label == 1){
					struct_arr[ cus_num[i][j] ].label = -1;
					while(j<8){ cus_num[i][j] = cus_num[i][j+1]; j++;}
					cus_num[i][7] = -1;	j=8; i=N;
				}
			}
		break;

		case 2:
			for (i = 0; i < N; ++i)
			for (j = 8; j < 11; ++j){
				if(struct_arr[ cus_num[i][j] ].label==2){
					struct_arr[ cus_num[i][j] ].label = -1;
					while(j<11){ cus_num[i][j] = cus_num[i][j+1]; j++;}
					cus_num[i][10] = -1; j=11; i=N;
				}
			}
		break;

		case 3:
			for (i = 0; i < N; ++i)
			for (j = 11; j < 13; ++j){
				if(struct_arr[ cus_num[i][j] ].label == 3){
					struct_arr[ cus_num[i][j] ].label = -1;
					while(j<13){ cus_num[i][j] = cus_num[i][j+1]; j++;}
					cus_num[i][12] = -1; j=13; i=N;
				}
			}
		break;

		case 4:
			for (i = 0; i < N; ++i)
			for (j = 13; j < 15; ++j){
				if(struct_arr[ cus_num[i][j] ].label == 4){
					struct_arr[ cus_num[i][j] ].label = -1;
					while(j<15){ cus_num[i][j] = cus_num[i][j+1]; j++;}
					cus_num[i][14] = -1; j=15; i=N;
				}
			}
		break;
	}
}