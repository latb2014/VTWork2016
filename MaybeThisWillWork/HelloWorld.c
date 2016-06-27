/*
 * HelloWorld.c
 *
 *  Created on: May 17, 2016
 *      Author: Barrett
 *      Introductory project to pthreads, generally messing around with
 *      mutexes and condition variables along with threads
*/
#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//MUTEX
pthread_mutex_t amutex = PTHREAD_MUTEX_INITIALIZER;
//CONDITION VARIABLE
pthread_cond_t got_request = PTHREAD_COND_INITIALIZER;

void *threadFunc(void *arg){
	//CASTING ARGUMENT TO TYPE DESIRED
	char *str;
	str = (char*)arg;
	//wait on condition variables, all condition variables must be surrounded by mutexes
	pthread_mutex_lock(&amutex);
	int rc = pthread_cond_wait(&got_request, &amutex);
	pthread_mutex_unlock(&amutex);
	if (rc == 0){
		for (int i = 0; i < 5; i++){
				usleep(1000000);//rest for 1 second
				printf("%s\n", str);//print argument
				fflush(stdout);
			}
	}
	return NULL;

}

void *threadFunc2(void *arg){
	//CASTING ARGUMENT TO TYPE DESIRED
	int *x;
	x = (int*)arg;
	//wait on condition variables, all condition variables must be surrounded by mutexes
	pthread_mutex_lock(&amutex);
	int rc = pthread_cond_wait(&got_request, &amutex);
	pthread_mutex_unlock(&amutex);
	if (rc==0){
		for (int i = *x; i < 10; i++){
				usleep(1000000);//rest for 1 second
				printf("%d\n", i);//prints from x to 10
				fflush(stdout);
			}
	}
	return NULL;

}

void *threadFunc3(void *arg){
	//CASTING ARGUMENT TO TYPE DESIRED
	char *str;
	str = (char*)arg;

	for (int i = 0; i < 50; i++){
		usleep(100000);//rest for 100 miliseconds or .1 seconds
		printf("%s\n", str);//print argument
		fflush(stdout);
		if ( i == 25){//when i = 25 let the rest of the threads go
			pthread_mutex_lock(&amutex);
			pthread_cond_broadcast(&got_request);//RELEASES ALL WHO ARE WAITING ON got_request VARIABLE
			//*NOTE* pthread_cond_signal(&got_request) will release just one thread waiting not all of them
			pthread_mutex_unlock(&amutex);
		}
	}
	return NULL;

}

int main() {
	//initializing threads
	pthread_t pth;
	pthread_t pth2;
	pthread_t pth3;
	//dynamically allocating pth2Arg pointer data
	int *pth2Arg = malloc(sizeof(*pth2Arg));
	*pth2Arg = 1;//dereference to set equal to 1
	//CREATING THREADS
	//pthread_create(address of thread to make, NULL, function thread will run, argument to pass to thread function);
	//thread will begin executing function immediately after created
	pthread_create(&pth,NULL,threadFunc,"what up playa");
	pthread_create(&pth2,NULL,threadFunc2, pth2Arg);
	pthread_create(&pth3,NULL,threadFunc3, "hey");
	//JOINING THREADS
	//pthread_join(thread you want to join, variable for return from pthread_exit() to be stored in);
	//join will wait for threads to complete before main method exits
	pthread_join(pth3, NULL);
	pthread_join(pth, NULL);
	pthread_join(pth2, NULL);
	//print stuff
	for (int i = 0; i < 5; i++){
		usleep(1000000);//stall execution for argument number of microseconds (1 and 6 zeroes is one second)
		printf("nthn much fam hbu\n");
		fflush(stdout);
	}
	return 0;
}









