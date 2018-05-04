#include "rog.h"

/*####################################################
#	SCREEN FUNCTIONS
####################################################*/
//Initializes pdcurses and sets up the screen.
int screenSetUp()
{
	GLOBAL_MAX_HEIGHT = 25;
	GLOBAL_MAX_WIDTH  = 100;

	/*
	GLOBAL_MAX_WIDTH = getmaxx();
	GLOBAL_MAX_HEIGHT = getmaxy();
	*/
	initscr();
	noecho();
	keypad(stdscr, TRUE);

	//printw("Welcome to HoboRogue (%d,%d) - Press q to quit\n", GLOBAL_MAX_WIDTH, GLOBAL_MAX_HEIGHT);

	//printFrame();
	refresh();

	return 1;
}

void printFrame()
{
	int x, y;

	//Print top and bottom of active display
	for(x = 0; x<GLOBAL_MAX_WIDTH; x++)
	{
		mvprintw(0, x, "-");
		mvprintw(GLOBAL_MAX_HEIGHT, x, "-");
	}

	//Print edges of active display
	for(y = 1; y < GLOBAL_MAX_HEIGHT; y++)
	{
		//Print actual walls
		mvprintw(y, 0,"|");
		mvprintw(y, GLOBAL_MAX_WIDTH, "|");
	}

	//Print the corners of the Active display
	mvprintw(0,0, "+");
	mvprintw(GLOBAL_MAX_HEIGHT, GLOBAL_MAX_WIDTH, "+");
	mvprintw(0, GLOBAL_MAX_WIDTH, "+");
	mvprintw(GLOBAL_MAX_HEIGHT, 0, "+");

	refresh();

}

void printInnerFrame()
{
	int x, y;

	//Print top and bottom of active display
	for(x = 0; x<GLOBAL_MAX_WIDTH; x++)
	{
		mvprintw(1, x, "-");
		mvprintw(GLOBAL_MAX_HEIGHT-1, x, "-");
	}


	for(y = 1; y < GLOBAL_MAX_HEIGHT; y++)
	{
		//Print inner walls
		mvprintw(y, 1,"|");
		mvprintw(y, GLOBAL_MAX_WIDTH-1, "|");
	}

	//Print the inner corners
	mvprintw(1,1, "+");
	mvprintw(GLOBAL_MAX_HEIGHT-1, GLOBAL_MAX_WIDTH-1, "+");
	mvprintw(1, GLOBAL_MAX_WIDTH-1, "+");
	mvprintw(GLOBAL_MAX_HEIGHT-1, 1, "+");
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