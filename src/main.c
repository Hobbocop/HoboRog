#include "rog.h"

//Main function
int main()
{
	//Variables
	int ch;
	Level * level;
	Coords newPosition;
	GLOBAL_MAX_HEIGHT = 25;
	GLOBAL_MAX_WIDTH  = 100;

	//Init stuff
	screenSetUp();
	level = createLevel(1);
	printGameHud(level);
	move(level->user->position->y, level->user->position->x);

	//Main game loop
	while((ch = getch()) != 'q'){
		newPosition = handleInput(ch, level->user);
		checkPosition(newPosition, level);
		moveMonsters(level);
		printGameHud(level);
		move(level->user->position->y, level->user->position->x);
		refresh();
	}

	//getch();
	endwin();
	return 0;
}
