#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 500

int rec(int array[], int find, int element, int inner){

	if (element >= N)
		return 0;

	if (inner >= N)
		return rec(array, find, element + 1, element + 2);

	if (array[element] + array[inner] == find)
		return 1 + rec(array, find, element, inner + 1);

	return rec(array, find, element, inner + 1);
}

int main(int argc, char const *argv[]) {

	int array[N], i, find = 58, count = 0;

   	for( i = 0 ; i < N ; i++ )
    	array[i] = i;
	
	clock_t begin = clock();

	count = rec(array, find, 0, 1);

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("element number: %d time: %f\n", N, time_spent);

	return 0;
}