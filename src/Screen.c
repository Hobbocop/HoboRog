#include "rog.h"

/*####################################################
#	SCREEN FUNCTIONS
####################################################*/
//Initializes pdcurses and sets up the screen.
int screenSetUp()
{
	initscr();
	printw("Welcome to HoboRogue - Press q to quit\n");
	noecho();
	refresh();

	return 1;
}

int printGameHud(Level* level)
{
	mvprintw(25,0, "Floor: %d",level->lvl);
	printw("    Exp: %d",level->user->exp);
	printw("    Level: %d",level->user->lvl);
	printw("    HP: %d(%d)",level->user->hp,level->user->maxHp);


	printw("    Attack: %d", level->user->attack);
	printw("    Defense: %d", level->user->defense);
	printw("    Gold: %d", level->user->gold);
	printw("    ");

	return 1;
}