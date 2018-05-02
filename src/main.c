#include "rog.h"
#include "mainMenu.h"


int gameLoop()
{
	//Variables
	int ch = '\0';
	Level * level;
	Coords newPosition;

	printFrame();
	level = createLevel(1);
	printGameHud(level);
	//move(level->user->position->y, level->user->position->x);

	//Main game loop
	while(ch != 'q'){
		newPosition = handleInput(ch, level->user);
		checkPosition(newPosition, level);
		moveMonsters(level);
		printGameHud(level);
		drawLevel(level);
		//move(level->user->position->y, level->user->position->x);

		if(level->user->hp <= 0){
			clear();
			mvprintw(1,1,"You have died, press any button to return to main menu");
			getch();
			return -1;
		}

		ch = getch();
		//drawLevel(level);
		refresh();
	}
}

void menuLoop()
{
	int choice, check;
	char* choices[] = {"Start new Game", "Quit game", "Secret Option 3"};

	//Enter eternal loop to check main menu
	while(TRUE){
		choice = mainMenu(3, choices);

		switch(choice){
			//Start game has been pressed
			case START_GAME:
				//Game returns because player died, back to main menu
				if(gameLoop()==-1){
					clear();
					break;
				} else { //If player quit by himself, just exit
					clear();
					return;
				}
			//If quit game was chosen, just exit
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
