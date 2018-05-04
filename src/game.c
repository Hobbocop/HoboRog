#include "rog.h"
#include "mainMenu.h"

void generateFirstLevel(gameSet* game)
{
	game->levels[game->currentLevel] = createLevel(1);
	game->currentLevel++;
}

void generateNextLevel(gameSet* game)
{
	game->levels[game->currentLevel] = createLevel(game->currentLevel+1);
	copyPlayerStats(game->levels[game->currentLevel-1]->user,
				    game->levels[game->currentLevel]->user);
	game->currentLevel++;
}

//Draws the entire game, character and monsters as well as the HUD
void render(gameSet * game)
{
	printFrame();
    printGameHud(game->levels[game->currentLevel - 1]);
    drawLevel(game->levels[game->currentLevel - 1]);
}

int gameLoop(gameSet* game)
{
	//Variables
	int ch = '\0';
	Level* level;
	Coords newPosition;
	Player* temp;

	//printFrame();
	if(game->currentLevel==0)
		generateFirstLevel(game);

	level = game->levels[game->currentLevel-1];

	//Main game loop, every pass is based on the keyboard input at the end of last and counts as a full turn
	while(ch != 'q'){
		//Cheat key to go down one floor
		if(ch == 'f'){
			//Have reached the bottom, untold riches await!
			if(game->currentLevel==game->maxLevel){
				clear();
				mvprintw(1,1,"You have cleared the game!");
				getch();
				return -1;
			}
			//Else, generate a new level
			generateNextLevel(game);
			level = game->levels[game->currentLevel-1];
		}

		//Handle all the logic and update the game
		newPosition = handleInput(ch, level->user);
		checkPosition(newPosition, level);
		moveMonsters(level);

		//Draw the entire game
		render(game);

		//Return if player has died this turn
		if(level->user->hp <= 0){
			clear();
			mvprintw(1,1,"You have died, press any button to return to main menu");
			getch();
			return -1;
		}

		//Get new input from player
		ch = getch();

		refresh();
	}
}
