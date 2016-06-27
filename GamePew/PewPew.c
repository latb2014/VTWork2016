/*
 * PewPew.c
 *
 *  Created on: May 24, 2016
 *      Author: Barrett
 *      A game where the user races the computer in typing pew, the first
 *      person to get to 15 wins, this uses usleep and threads a lot
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

//GLOBAL VARIABLES essentially booleans
int userwin = 0;//false
int compwin = 0;//false

void *userfunc(void *arg){
	//strings
	char pew[10];//user input
	char rightstring[4] = "pew";//to check if input correct
	//ints
	int answ;//essentially a boolean, 0=false 1=true
	int score = 0;

	while(score < 15 && compwin == 0){//scan for pew until user wins or computer wins
		scanf("%s", pew);
		answ = strcmp(pew, rightstring);
		if (answ == 0 && compwin == 0){//check if entry was right and computer still hasn't won
			score++;
		}
	}
	if(compwin == 0 && score >= 15){//if computer still hasnt won and score at or above 15 you win
		userwin = 1;//win=true
		printf("\n\n	You win!");
		fflush(stdout);
	}
	return NULL;//end
}

void *compfunc(void *arg){
	int compscore = 0;
	int sleeptime;
	//DEFINE ARGUMENT(difficulty level)
	int *compmode;
	compmode = (int*) arg;
	//EASY
	if(*compmode == 1){
		sleeptime = 2000000;//rest 2 seconds between each print
	}
	//MEDIUM
	else if(*compmode == 2){
		sleeptime = 800000;//rest for .8 seconds between each print
	}
	//IMPOSSIBLE
	else{
		sleeptime = 300000;//rest for .3 seconds between each print
	}

	while(compscore < 15 && userwin == 0){//print pew every set number of seconds until user or computer wins
		printf("                    pew\n");
		fflush(stdout);
		if(userwin == 0){//if user hasn't won yet add to the score
			compscore++;
		usleep(sleeptime);//sleep depending on difficulty level
		}
	}
	if(userwin == 0 && compscore >= 15){//if user still hasn't won and computer has score of 15 or higher computer wins
		compwin = 1;//set to true
		printf("\n\n	The compter wins...");
		fflush(stdout);
	}
	return NULL;//end
}

int main(){
	int *mode = malloc(sizeof(*mode));//game mode
	char *answermode[30];//string intake

	//SETTING UP THE GAME

	printf("WELCOME TO PEW. FIRST ONE TO 15 WINS\n\n");
	fflush(stdout);
	usleep(1000000);
	printf("How hard would you like it to be? Enter the number\n\n1.Jesus Lord this is easy af\n2.Ok this is pretty hard\n3.KILL ME\n\n");
	fflush(stdout);
	scanf("%d", mode);
	fflush(stdout);
	if(*mode == 1){
		*answermode = "Jesus Lord this is easy af";
	}
	else if (*mode == 2){
		*answermode = "Ok this is pretty hard";
	}
	else if (*mode == 3){
		*answermode = "KILL ME";
	}
	printf("Wonderful! You chose the %s setting! Have fun!\n\n", *answermode);
	fflush(stdout);
	usleep(1000000);
	printf("Ready?\n\n");
	fflush(stdout);
	usleep(1000000);
	printf("3...");
	fflush(stdout);
	usleep(1000000);
	printf("2...");
	fflush(stdout);
	usleep(1000000);
	printf("1...\n");
	fflush(stdout);
	usleep(1000000);
	printf("____________\n|    GO    |\n------------");

	//set up threads
	pthread_t user;
	pthread_t computer;
	//create threads
	pthread_create(&user, NULL, userfunc, NULL);
	pthread_create(&computer, NULL, compfunc, mode);
	//join the threads
	pthread_join(user, NULL);
	pthread_join(computer, NULL);
	usleep(10000000);//wait for 10 seconds
}
