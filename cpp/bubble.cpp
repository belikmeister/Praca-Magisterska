#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
void swap(int *num1, int *num2);

int main (int argc, char *argv[]) {
	char *p;
    auto power = strtol(argv[1],&p,10);
    auto threadNum = strtol(argv[2],&p,10);
    int SIZE =pow(2,power);
    int setNumThreads=threadNum;
	
    std::vector<int> A;
	for(int i=0;i<SIZE;i++)
	{
	    A.push_back(rand()%(63000+1-0)+0);
	}

	int N = SIZE;
	int i=0, j=0; 
	int first;
	double start,end;
	start=omp_get_wtime();
	for( i = 0; i < N-1; i++ )
	{
		first = i % 2; 
        omp_set_dynamic(0);     //Dynamika zmiany rdzeni
        omp_set_num_threads(setNumThreads);  //Ilość rdzeni używanych przez program
		#pragma omp parallel for default(none),shared(A,first,N)
		for( j = first; j < N-1; j += 1 )
		{
			if( A[ j ] > A[ j+1 ] )
			{
				swap(&A[j], &A[j+1]);
			}
		}
	}
end=omp_get_wtime();
	/*for(i=0;i<N;i++)
	{
		printf(" %d",A[i]);
	}*/

printf("\n");
printf("\n-------------------------\n CZAS WYKONANIA ROWNOLEGLEGO = %f",(end-start));
printf("\n-------------------------\n KORZYSTAJAC Z RDZENI = %d",(setNumThreads));
printf("\n-------------------------\n ROZMIAR PROBY = %d",(SIZE));
printf("\n");

}

void swap(int *num1, int *num2)
{

	int temp = *num1;
	*num1 =  *num2;
	*num2 = temp;
}