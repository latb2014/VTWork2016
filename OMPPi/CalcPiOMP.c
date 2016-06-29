/*
 * PiCode.c
 *
 *  Created on: May 25, 2016
 *      Author: Barrett
 *      Uses the Monte Carlo method of pi calculation and pthreads
 *      to accurately and consistently approximate pi, getting more
 *      accurate as the number of threads increase
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <windows.h>
#include <unistd.h>

//GLOBAL VARIABLE
int threadcount = 1000;//number of threads created


int main(){
	int pointsinside = 0;//if addornot is true(1) add one
	double pi;//store actual finished value of pi
	//int idnum = 0;
	double rand1;
	double rand2;
	int run = 0;
	double answ;

	omp_set_num_threads(threadcount);
	//srand(9);

	//seed the rand function ONLY DO ONCE AND NOT IN ANY THREADS, THE NUMBERS WILL BECOME NOT RANDOM IF YOU DO AND IT WILL SKEW RESULTS

	#pragma omp parallel num_threads(threadcount) shared(pointsinside) private(answ, rand1, rand2, run)
	{

		srand(omp_get_thread_num()+1.5);
		while(run < 100){
			rand1 = (double)rand()/RAND_MAX;
			rand2 = (double)rand()/RAND_MAX;
			//#pragma omp atomic
				//idnum++;

			printf("-------------------------\n| %f...%d..%f |\n-------------------------\n", rand1, run, rand2);
			fflush(stdout);
			answ = (rand1*rand1)+(rand2*rand2);

			if(answ < 1){
				#pragma omp atomic
					pointsinside++;
				//printf("\n\nadded: %d  :  %f\n\n", pointsinside, answ);
			}
				run++;
		}

	}


	//MATH, SEE MONTE CARLO PI CALCULATION
	printf("%d.....threads: %d", pointsinside, threadcount*100);
	pi = 4 * ((double)pointsinside/(threadcount*100));//4*(number of points inside/total number of threads)
	printf("\n\nPi is estimated to:  %f\n\n", pi);
	fflush(stdout);
}






