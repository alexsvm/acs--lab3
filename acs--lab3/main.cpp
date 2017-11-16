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

	// task 3 ////////////////////////////////////////////////////////////////////////////
	printf("\n      >>> Task 3 <<<< \n");

#define Size3 3
	int A3[Size3], B3[Size3][Size3], C3[Size3];
	for (int i = 0; i < Size3; i++) { // init A[] B[] ry random
		A3[i] = rand() % 10;
		C3[i] = 0;
		for (int j = 0; j < Size3; j++)
			B3[i][j] = rand() % 10;
	}
	printf("Вектор А = { %d", A3[0]);
	for (int i = 1; i < Size3; i++)
		printf(", %d", A3[i]);
	printf(" }\n");

	printf("Матрица B:\n");
	for (int i = 0; i < Size3; i++) {
		printf("{ %d", B3[i][0]);
		for (int j = 1; j < Size3; j++)
			printf(", %d", B3[i][j]);
		printf(" }\n");
	}

#pragma omp parallel num_threads(4) shared(A3, B3, C3)
	{
		int ThreadId = omp_get_thread_num();
#pragma omp for
		for (int j = 0; j < Size3; j++) {
			for (int i = 0; i < Size3; i++) {
				C3[j] += A3[i] * B3[i][j];
				printf("Thread %d: C3[%d] += A3[%d] * B3[%d][%d] = %d*%d = %d\n", ThreadId, j, i, i, j, A3[i], B3[i][j], C3[j]);
			}
		}
	}

	printf("Вектор C = { %d", C3[0]);
	for (int i = 1; i < Size3; i++)
		printf(", %d", C3[i]);
	printf(" }\n");


	// task 4 ////////////////////////////////////////////////////////////////////////////
	printf("\n      >>> Task 4 <<<< \n");
	printf("  ");
	for (int i = 1; i <= 9; i++) // Print head
		printf("\t%d", i);
	printf("\n--");
	for (int i = 1; i <= 9; i++) // Print head
		printf("\t--");
	printf("\n");
#pragma omp parallel num_threads(4)
	{
#pragma omp for ordered
		for (int i = 1; i <= 9; i++) {
#pragma omp ordered
			{
				printf("%d |", i);
				for (int j = 1; j <= 9; j++)
					printf("\t%d", i*j);
				printf("\n");
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////
	printf("\n==========================================================\n");
	printf("Press Enter to exit...");
	getchar();
}