#include "rog.h"

/*####################################################
#	SCREEN FUNCTIONS
####################################################*/
//Initializes pdcurses and sets up the screen.
int screenSetUp()
{
	initscr();
	printw("Welcome to HoboRogue (%d,%d) - Press q to quit\n", GLOBAL_MAX_WIDTH, GLOBAL_MAX_HEIGHT);

	mvprintw(GLOBAL_MAX_HEIGHT, GLOBAL_MAX_WIDTH, "+");
	mvprintw(0, GLOBAL_MAX_WIDTH, "+");
	mvprintw(GLOBAL_MAX_HEIGHT, 0, "+");

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