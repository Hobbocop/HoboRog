#include "rog.h"

#define TRUE 1
#define FALSE 0

//Main function
int main()
{
	//Variables
	int ch;
	Level * level;
	Coords newPosition;

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
	}

	//getch();
	endwin();
	return 0;
}
