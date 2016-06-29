/*
 * PiCode.c
 *
 *  Created on: May 25, 2016
 *      Author: Barrett
 *      Uses the Monte Carlo method of pi calculation and pthreads
 *      to accurately and consistently approximate pi, getting more
 *      accurate as the number of threads increase
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

//GLOBAL VARIABLE
int threadcount = 102400;//number of threads created 250000

//STRUCTURES
struct randoms{//used to pass the two random numbers
	double rand1;
	double rand2;
};

void *piseries(void *arg){
	//*NOTE* DON'T SEED RANDOM NUMBERS (srand()) IN THE THREAD FUNCTION,
	//you must seed the random function once in the main method so its only seeded once as a constant
	//addornot has dynamically allocated data
	int *addornot = malloc(sizeof(*addornot));//add or not is returned as 0 or 1, a boolean for C

	struct randoms *nums = (struct randoms*)arg;
	//gets random numbers created in main()
	double x = nums->rand1;
	double y = nums->rand2;
	//THE MATH, REFER TO MONTE CARLO PI CALCULATION
	double answ = (x*x)+(y*y);
	//DEBUGGINGprintf("\n\n------------\n|    %f...%f    |\n------------\n\n", x, y);
	*addornot = 0;//initially false
	if (answ < 1){
		*addornot = 1;//TRUE
		pthread_exit(addornot);//return addornot to pthread_join()
	}
	else{//FALSE
		pthread_exit(addornot);//return addornot to pthread_join
	}
	return NULL;
}

int main(){
	void *incircle;//recieve the addornot variable when pthread_exit() is called
	int pointsinside = 0;//if addornot is true(1) add one
	double pi;//store actual finished value of pi
	struct randoms randm;//random numbers for pthreads

	//INITIALIZING THE THREADS
	pthread_t threads[threadcount];//array of threads with custom size of global variabel threadcount
	srand(3645783);//seed the rand function ONLY DO ONCE AND NOT IN ANY THREADS, THE NUMBERS WILL BECOME NOT RANDOM IF YOU DO AND IT WILL SKEW RESULTS

	for (int i = 0; i < threadcount; i++){//create random numbers, threads and joins the threads while printing out status of the process
		//assign random numbers to structure, DIVIDE BY RAND_MAX NOT ESTIMATED MAX OR ELSE RESULTS WILL BE SKEWED
		randm.rand1 = (double)rand()/RAND_MAX;
		randm.rand2 = (double)rand()/RAND_MAX;
		//create and join threads
		pthread_create(&threads[i], NULL, piseries, (void *)&randm);
		pthread_join(threads[i], &incircle);
		if(*(int*)incircle == 1){//incircle is returned by pthread_exit in the piseries function
				pointsinside++;
				//DEBUGGINGprintf("YES");
				//DEBUGGINGfflush(stdout);
		}
		//printing benchmark points
		if((double)i/threadcount == .25){
			printf("  25%%  ");
			fflush(stdout);
		}
		else if((double)i/threadcount == .5){
			printf("  50%%  ");
			fflush(stdout);
		}
		else if((double)i/threadcount == .75){
			printf("  75%%  ");
			fflush(stdout);
		}
	}//end for
	//MATH, SEE MONTE CARLO PI CALCULATION
	pi = 4 * ((double)pointsinside/threadcount);//4*(number of points inside/total number of threads)
	printf("\n\nPi is estimated to:  %f\n\n%d", pi, pointsinside);
	fflush(stdout);
}








