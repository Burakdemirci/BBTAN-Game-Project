/**********************************************/
/* Burak Demirci                              */
/* burakdemirci@gtu.edu.tr                    */
/* 141044091                                  */
/* Yaz Odevi                                  */
/**********************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include "Game.h"

int Random(int mod);

int main()
{
    StartScreen();

   return 0;
}

int Random(int mod)
{
	srand(time(NULL));

	return rand()%mod;
}


