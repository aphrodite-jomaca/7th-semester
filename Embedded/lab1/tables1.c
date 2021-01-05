#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main()
{
	int i;
	int N = 100000000;
	double *x1, *x2, *x3, *y;
	double a1 = 0.5;
	double a2 = 1;
	double a3 = 1.5;
	struct timeval start_time, end_time;

	x1 = (double *)malloc(N * sizeof(double));
	x2 = (double *)malloc(N * sizeof(double));
	x3 = (double *)malloc(N * sizeof(double));
	y = (double *)malloc(N * sizeof(double));

	//Do not modify this loop
	for (i = 0; i <= N - 1; i++)
	{
		x1[i] = (double)i * 0.5;
		x1[i] = (double)i * 0.4;
		x2[i] = (double)i * 0.8;
		x3[i] = (double)i * 0.2;
		y[i] = 0;
	}

	gettimeofday(&start_time, NULL);
	/*
	Τhis is the basic loop of tables.c. Isolate it in file tables_orio.c,
	in which all the parameters for Design Space Exploration (DSE) and loop 
	transfornations should be defined.
	*/
	//FOR RANDOM USE:
	//arg algorithm  = 'Random'
	//arg time_limit = 10;
	//arg total_runs = 10;
	//FOR SIMPLEX USE:
	// arg algorithm = 'Simplex';
	//arg time_limit = 10;
	//arg total_runs = 10;
	//arg simplex_local_distance = 2;
	//arg simplex_reflection_coef = 1.5;
	//arg simplex_expansion_coef = 2.5;
	//arg simplex_contraction_coef = 0.6;
	//arg simplex_shrinkage_coef = 0.7;
	for (i = 0; i <= N - 1; i++)
	{
		//This loop needs to be modified after Orio's execution...
		y[i] = y[i] + a1 * x1[i] + a2 * x2[i] + a3 * x3[i];
	}

	gettimeofday(&end_time, NULL);
	printf("%ld ", (end_time.tv_sec - start_time.tv_sec) * 1000000 + end_time.tv_usec - start_time.tv_usec);
	return 0;
}