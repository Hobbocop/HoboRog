#include "rog.h"
#include "mainMenu.h"

void menuLoop()
{
	int choice;
	choice = -1; //TO show that there has been no choice made
	char* choicesMain[] = {"Start new Game",
						"Quit game",
						"Secret Option 3 (inert"};
	char* choicesPause[] = {"Start new Game",
						"Continue",
						"Quit game",
						"Secret Option 3 (inert)"};

	gameSet game;
    game.currentLevel = 0;
    game.maxLevel = 9;

	//Enter eternal loop to check main menu
	while(TRUE){
		if (choice == -1)
		{
			choice = mainMenu(2, choicesMain);
			if(choice == 1)
				choice = QUIT_GAME;
		}

		switch(choice){
			//Start game has been pressed
			case START_GAME:
				game.currentLevel = 0;

			case CONTINUE_GAME:
				//Game returns because player died, back to main menu
				if(gameLoop(&game)==-1){
					clear();
					choice = -1;
				} else { //If player quit by himself, just exit
					clear();
					choice = mainMenu(3, choicesPause);
				}
				break;

			//If quit game was chosen, just exit
			case QUIT_GAME:
				clear();
				return;
		}
	}
}

//Main function
int main()
{
	//Init stuff
	screenSetUp();

	//Enter menu loop
	menuLoop();

	endwin();
	return 0;
}
