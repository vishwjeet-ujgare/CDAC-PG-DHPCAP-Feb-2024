#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#define N 10000
/*
				N  PRIME_NUMBER

				1           0
			   10           4
			  100          25
			1,000         168
		   10,000       1,229
		  100,000       9,592
		1,000,000      78,498
	   10,000,000     664,579
	  100,000,000   5,761,455
	1,000,000,000  50,847,534

*/

int main()
{
	int i, j, rank, size, flag, count, local_count;
	double start_time, end_time, execution_time;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int range = N / size;
	int start = rank * range + 2;
int end = (rank +1)*range + 1;
	count = 1; // 2 is prime. Our loop starts from 3

	gettimeofday(&start_time, NULL);

	for (i = 3; i < N; i++)
	{
		flag = 0;
		for (j = 2; j < i; j++)
		{
			if ((i % j) == 0)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			count++;
		}
	}

	gettimeofday(&stop_time, NULL);
	exe_time = (stop_time.tv_sec + (stop_time.tv_usec / 1000000.0)) - (start_time.tv_sec + (start_time.tv_usec / 1000000.0));

	printf("\n Number of prime numbers = %d \n Execution time is = %lf seconds\n", count, exe_time);
}
