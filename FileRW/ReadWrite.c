/*
 * ReadWrite.c
 *
 *  Created on: May 27, 2016
 *      Author: Barrett
 *      Uses Semaphores to solve a more basic problem than the
 *      one presented in ThreadingFileIO, threads alternating
 *      reading and writing to a file
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

//SEMAPHORES
sem_t printerS;//for writers
sem_t scannerS;//for readers

//GLOBAL VARIABLES
int threadcount = 64;//number of threads created

//STRUCTURES
struct sFileAndId{//for readers or scanners
	FILE *stFile;
	int sidNum;
};
struct pFileAndId{//for writers or printers
	FILE *ptFile;
	int pidNum;
};

static void cat(FILE *fp)//reads the file
{
	char buffer[4096];//essentially a string
	rewind(fp);//sets cursor back to beginning of file
    while (fgets(buffer, sizeof(buffer), fp) != NULL){//honestly bro I found this online I don't really know what tf its doing

    	printf("%s\n\n", buffer);//prints out to screen the line of the file
        fflush(stdout);
    }
}


void *printing(void *arg){//WRITERS
	sem_wait(&printerS);//printers wait for one to be let go by the scanner

	FILE *pFile;
	int pId;
	struct pFileAndId *prThreadInfo = (struct pFileAndId *) arg;
	//Get the Id and File from arg structure and transfer it to local variables
	pId = prThreadInfo->pidNum;
	pFile = prThreadInfo->ptFile;

	fprintf(pFile, "%dHello", pId);//Print to the text file IdNumberHello
	sem_post(&scannerS);//let next scanner go
	return NULL;//end
}


void *scanning(void *arg){//READERS
	sem_wait(&scannerS);//Initialized at 1 so alternation starts here, all other scanners wait to be called by a printer

	FILE *sFile;
	int sId;
	struct sFileAndId *prThreadInfo = (struct sFileAndId *) arg;
	//Get the Id and File from arg structure and transfer it to local variables
	sId = prThreadInfo->sidNum;
	sFile = prThreadInfo->stFile;

    printf("%d: ", sId);//print IdNumber:
    fflush(stdout);
	cat(sFile);//read and prints the file
	sem_post(&printerS);//let next printer go
	return NULL;//end
}

int main(){
	FILE *fp;
	fp = fopen("C:\\Users\\Barrett\\fio.txt", "r+");//open text file
	//Initializing Semaphores
	sem_init(&printerS, 0, 0);//lock for printers, start at zero, first number is always zero in initializer
	sem_init(&scannerS, 0, 1);//lock for scanners, start at one
	//Create new structures for scanners(readers) and printers(writers), pass files to the structures
	struct pFileAndId pThreadArgs;
	pThreadArgs.ptFile = fp;//pass file
	struct sFileAndId sThreadArgs;
	sThreadArgs.stFile = fp;//pass file

	pthread_t threads[threadcount];//array of threads the size of how many threads I want
	//INITIALIZING THREADS
	for (int i = 0; i < threadcount; i++){//initialize threads using a for loop and alternating, evens write or print and odds read or scan
		if(i%2 == 0){
			pThreadArgs.pidNum = i;//number that the pthread was created on in the for loop sent to its structure
			pthread_create(&threads[i], NULL, printing, (void *)&pThreadArgs);
			//DEBUGGINGprintf("%d:  addedp\n\n", i);
			//DEBUGGINGfflush(stdout);
		}
		else{
			sThreadArgs.sidNum = i;//number that the pthread was created on in the for loop sent to its structure
			pthread_create(&threads[i], NULL, scanning, (void *)&sThreadArgs);
			//DEBUGGINGprintf("%d:  addeds\n\n", i);
			//DEBUGGINGfflush(stdout);
		}

	}
	for(int m = 0; m < threadcount; m++){//joining makes the main method sleep until the threads finish executing
		pthread_join(threads[m], NULL);
		//DEBUGGINGprintf("\n%d\n",m);
		//DEBUGGINGfflush(stdout);

		}

	fclose(fp);//close text file
	return 0;
}



