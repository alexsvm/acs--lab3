#include <omp.h> 
#include <stdio.h> 
#include <locale.h>
#include <stdlib.h>

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

#define Size1 8
	int A[Size1], B[Size1], C[Size1];
	for (int i = 0; i < Size1; i++) { // init A[] B[] ry random
		A[i] = rand() % 100;
		B[i] = rand() % 100;
	}

#pragma omp parallel num_threads(4) shared(A, B)
	{
		int ThreadId = omp_get_thread_num();
#pragma omp for
		for (int i = 0; i < Size1; i++) {
			C[i] = A[i] + B[i];
			printf("Thread %d: C[%d] = A[%d]+B[%d] = %d+%d = %d\n", ThreadId, i, i, i, A[i], B[i], C[i]);
		}
	}

	// task 2 ////////////////////////////////////////////////////////////////////////////
	printf("\n      >>> Task 2 <<<< \n");

#define Size2 100
	int A2[Size2], B2[Size2];
	for (int i = 0; i < Size2; i++) { // init A[] B[] ry random
		A2[i] = rand() % 100;
		B2[i] = rand() % 100;
	}

	int sum = 0;

#pragma omp parallel num_threads(4) shared(A2, B2) reduction(+ : sum)
	{
		int ThreadId = omp_get_thread_num();
#pragma omp for
		for (int i = 0; i < Size2; i++) {
			sum += A2[i] * B2[i];
			printf("Thread %d: sum += A[%d]*B[%d] = %d*%d = %d\n", ThreadId, i, i, A2[i], B2[i], sum);
		}
	}
	printf("sum = %d\n", sum);

	//////////////////////////////////////////////////////////////////////////////
	printf("==========================================================\n");
	printf("Press Enter to exit...");
	getchar();
}