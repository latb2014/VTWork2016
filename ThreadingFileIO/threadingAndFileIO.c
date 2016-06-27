/*
 * ReadWrite.c
 *
 *  Created on: May 27, 2016
 *      Author: Barrett
 *      Alternates between reading and writing to a text file with a custom number of loops each
 *      reads or writes before they switch and
 *      a custom number of threads that are used to do this
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//locks with their partner condition variables, all condition variables need to use a lock
//writing
pthread_mutex_t writeMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t writeThreadRelease = PTHREAD_COND_INITIALIZER;
//reading
pthread_mutex_t readMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t readThreadRelease = PTHREAD_COND_INITIALIZER;
//interaction
pthread_cond_t rwInteraction = PTHREAD_COND_INITIALIZER;

//GLOBAL VARIABLES
int threadcount = 16;//threads created
int LOOPS = 10;//number of loops each action does
int writing = 0;//loop counter
int reading = 0;//loop counter


static void cat(FILE *fp)//reading the file
{
    char buffer[4096];//essentially a string
    rewind(fp);//sets cursor back to beginning of file
    while (fgets(buffer, sizeof(buffer), fp) != NULL){//honestly bro I found this online I don't really know what tf its doing
    	printf("reading");
    	fflush(stdout);
    }
}


void *printing(void *arg){
	FILE *pFile;
	pFile = (FILE *)arg;
	while(1){//first while
		pthread_mutex_lock(&writeMutex);
		pthread_cond_wait(&writeThreadRelease, &writeMutex);//holds all the threads except the executing one
		pthread_mutex_unlock(&writeMutex);
		if(writing < LOOPS){//first if
			//THIS WORKS. All threads have different Id's
			pid_t pId;
			pId = (int)pthread_self();//thread Id's assigned to it
			printf("W- %d\n", pId);
			fflush(stdout);
			//Writing to the file
			fprintf(pFile, "%dHello", pId);
			//increment global variable, make sure protected so wont get corrupted by other threads, could very likely cause logical errors if not treated properly
			writing++;
			//check again if writing >= 10
			if(writing >= LOOPS){//second if, GIVES TO READERS
				printf("W: Switch!\n\n");
				fflush(stdout);
				pthread_mutex_lock(&writeMutex);//condition variables must be surrounded by a mutex
				pthread_cond_signal(&readThreadRelease);//release a single read thread
				pthread_cond_wait(&rwInteraction, &writeMutex);//wait for the readers to signal for the writers to continue
				writing = 0;//reinstatiate global variable for next loop of writing once readers finish
				pthread_mutex_unlock(&writeMutex);//supposed to release the rest of the threads from writeGlobalLock that should then go directly to else
			}//end second if
		}//end first if
		pthread_mutex_lock(&writeMutex);
		pthread_cond_signal(&writeThreadRelease);//release a different thread, acting thread will get stuck at the top of the while loop again
		pthread_mutex_unlock(&writeMutex);
		printf("next print\n\n");
		fflush(stdout);
	}//end first while
	return NULL;
}


void *scanning(void *arg){//also referred to as readers
	FILE *sFile;
	pid_t sId;
	sFile = (FILE *) arg;
	while(1){//first while
		while(1){//second while
			//all readers wait until a writer signals for one to go back in the printing method
			pthread_mutex_lock(&readMutex);
			pthread_cond_wait(&readThreadRelease, &readMutex);//all readers get stopped here until writer releases one
			pthread_mutex_unlock(&readMutex);

			if(reading <= LOOPS){//first if, check that hasn't read more than preset loop value
				sId = (int)pthread_self();//get thread Id
				cat(sFile);//reads the file
				printf("\nR- %d\n", sId);
				fflush(stdout);
				//GLOBAL VARIABLE must be protected so isn't corrupted but could very likely cause logical errors if not treated properly
				reading++;
				//check after the add if reading is still smaller than LOOP
				if(reading >= LOOPS){//second if
					break;//goes to end of second while loop
				}//end second if
			}//end first if, all is well, continue in the first while loop
			pthread_mutex_lock(&readMutex);
			pthread_cond_signal(&readThreadRelease);//release a different thread, acting thread will get stuck at the top of the while loop again
			pthread_mutex_unlock(&readMutex);
		}//end second while
		//RELEASE THE WRITERS
		pthread_mutex_lock(&readMutex);
		pthread_cond_signal(&rwInteraction);//release a writer, acting thread will get stuck at the top of the while loop again
		pthread_mutex_unlock(&readMutex);
		reading = 0;//reinstatiate global variable for next loop of reading when writers finish
	}//end first while
	return NULL;
}

int main(){
	FILE *fp;
	fp = fopen("C:\\Users\\Barrett\\threadingPrCo.txt", "r+");//open text file

	pthread_t threads[threadcount];//array of threads the size of how many threads I want
	//INITIALIZING THREADS
	for (int i = 0; i < threadcount; i++){//initialize threads using a for loop and alternating, evens write or print and odds read or scan
		if(i%2 == 0){
			pthread_create(&threads[i], NULL, printing, (void *)fp);
			//DEBUGGINGprintf("%d:  addedp\n\n", i);
			//DEBUGGINGfflush(stdout);
		}
		else{
			pthread_create(&threads[i], NULL, scanning, (void *)fp);
			//DEBUGGINGprintf("%d:  addeds\n\n", i);
			//DEBUGGINGfflush(stdout);
		}

	}
	//As soon as all the threads are created, this signals for one writer to start
	pthread_mutex_lock(&writeMutex);
	pthread_cond_signal(&writeThreadRelease);//release one writer
	pthread_mutex_unlock(&writeMutex);
	//JOINING THREADS
	for(int m = 0; m < threadcount; m++){//joining makes the main method sleep until the threads finish executing
		pthread_join(threads[m], NULL);
		//DEBUGGINGprintf("\n%d\n",m);
		//DEBUGGINGfflush(stdout);

		}

	fclose(fp);//close file
	return 0;
}






