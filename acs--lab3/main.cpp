#include <omp.h> 
#include <stdio.h> 
#include <locale.h>

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Rus");

	/*int NumOfThreads;
	double start = omp_get_wtime();
#pragma omp parallel 
	{
		int ThreadId;
		ThreadId = omp_get_thread_num();
		NumOfThreads = omp_get_num_threads();
		printf("Hello, I am thread number %d from %d\n", ThreadId, NumOfThreads);
#pragma omp master
		{
			printf("I am master thread, number %d\n", ThreadId);
		}
	}
	double end = omp_get_wtime();
	printf("Running time = %f\n", end - start);*/

	// task 1 ////////////////////////////////////////////////////////////////////////////
	printf("\n      >>> Task 1 <<<< \n");


	//////////////////////////////////////////////////////////////////////////////
	printf("==========================================================\n");
	printf("Press Enter to exit...");
	getchar();
	getchar();
}