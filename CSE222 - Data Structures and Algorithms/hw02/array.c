#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 50000

int main(int argc, char const *argv[]) {

	int array[N], i, find = 58, count = 0;

   	for( i = 0 ; i < N ; i++ )
    	array[i] = i;
	
	clock_t begin = clock();

    for (int i = 0; i < N; ++i)
    	for (int j = i + 1; j < N; ++j)
    			if (array[i] + array[j] == find)
    				++count;

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("element number: %d time: %f\n", N, time_spent);

	return 0;
}