#include "rog.h"
#include "mainMenu.h"


int gameLoop()
{
	//Variables
	int ch;
	Level * level;
	Coords newPosition;

	printFrame();
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

		if(level->user->hp <= 0){
			clear();
			mvprintw(1,1,"You have died, press any button to return to main menu");
			getch();
			return -1;
		}

		refresh();
	}

}

void menuLoop()
{
	int choice;
	char* choices[] = {"Start new Game", "Quit game", "Secret Option 3"};

	//mainMenu(2, choices);

	while(TRUE){
		choice = mainMenu(3, choices);

		switch(choice){
			case START_GAME:
				gameLoop();
				clear();
				break;
			case QUIT_GAME:
				return;
		}
	}
}

//Main function
int main()
{
	//Init stuff
	screenSetUp();

	menuLoop();

	endwin();
	return 0;
}
