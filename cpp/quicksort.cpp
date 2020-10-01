
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <math.h>
#include <omp.h>
#include "quicksort-omp.h"



int main(int argc, char *argv[]){
//START
    char *p;
    int power = strtol(argv[1],&p,10);
    int threadNum = strtol(argv[2],&p,10);
    int lenArr =pow(2,power);
    int numthreads=threadNum;
//STOP

	int minMum = 1;
	int maxNum = lenArr;

	double startTime, stopTime;


	int* array_qs;

	array_qs = (int*) malloc(lenArr*sizeof(int));



	int i;
	srand(5); // seed
	for (i=0; i<lenArr; i++){
		// RAND_MAX = 2147483647 = INT_MAX 
		// printf("RAND_MAX %u \n", RAND_MAX );
		array_qs[i] = minMum+(rand()%maxNum);
		//printf("%d \n", array_qs[i] ); 
	}



    fflush(stdout);
	startTime = omp_get_wtime();
	quickSort_parallel(array_qs, lenArr, numthreads);
	stopTime = omp_get_wtime();

	printf("\nSortowanie trwało: %f sekund \n", (stopTime-startTime));
    printf("Rozmiar próbki:2^%d",power);
    printf("\nIlość rdzeni: %d\n\n",numthreads);

}