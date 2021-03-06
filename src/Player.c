#include "rog.h"


/*#############################################################################
#	PLAYER FUNCTIONS
#############################################################################*/
//INitializes a player struct and allocates memory
Player* playerSetUp()
{
	Player* newPlayer;
	newPlayer = malloc(sizeof(Player));
	newPlayer->position = malloc(sizeof(Coords));

	newPlayer->hp = 14;
	newPlayer->attack = 1;
	newPlayer->gold = 0;
	newPlayer->exp = 0;
	newPlayer->maxHp = 14;
	newPlayer->lvl = 1;
	newPlayer->defense=1;

	return newPlayer;
}

void copyPlayerStats(Player* old, Player* new)
{
	new->hp = old->hp;
	new->attack = 	old->attack;
	new->defense = 	old->defense;
	new->exp =		old->exp;
	new->lvl =		old->lvl;
	new->gold =		old->gold;
	new->maxHp =	old->maxHp;
}

int placePlayer(Room** rooms, Player* user)
{
	user->position->x = rooms[0]->coords.x+1;
	user->position->y = rooms[0]->coords.y+1;
}

//Moves the player character to the new x and y
int playerMove(Coords newPosition, Player* user, char ** level)
{
	user->position->y = newPosition.y;
	user->position->x = newPosition.x;
}

//Increments the experience counter, also signals when levelup
int addExp(Player* user, int xp)
{
	user->exp += xp;
	if(xp>=5 && user->lvl==1)
		levelUp(user);
	return 1;
}

//Increments the players level and stats accordingly
int levelUp(Player* user)
{
	//mvprintw(2,0, "Level up! Stats have been increased!");
	user->attack++;
	user->maxHp+=10;
	user->hp = user->maxHp;
	user->lvl++;
	return 1;
}

void drawPlayer(Player* user)
{
	attron(A_BOLD);
	mvprintw(user->position->y, user->position->x, "@");
	attroff(A_BOLD);
	move(user->position->y, user->position->x);
}


/*#############################################################################
#	Input functions
#############################################################################*/
//Handles the input and moves player if move is valid
Coords handleInput(int input, Player* user)
{
	Coords newPosition;

	switch(input)
	{
		//Move up
		case 'w':
		case 'W':
		case KEY_UP:
			newPosition.y = user->position->y-1;
			newPosition.x = user->position->x;
			break;

		//Move left
		case 'a':
		case 'A':
		case KEY_LEFT:
			newPosition.y = user->position->y;
			newPosition.x = user->position->x-1;
			break;

		//Move down
		case 's':
		case 'S':
		case KEY_DOWN:
			newPosition.y = user->position->y+1;
			newPosition.x = user->position->x;
			break;

		//Move right
		case 'd':
		case 'D':
		case KEY_RIGHT:
			newPosition.y = user->position->y;
			newPosition.x = user->position->x+1;
			break;

		//Do nothing,for now
		default:
			break;
	}
	return newPosition;
}

//Checks the position inidicated
int checkPosition(Coords newPosition, Level* level)
{
	Player* user;
	user = level->user;
	int space;
	switch(mvinch(newPosition.y, newPosition.x))
	{
		case '.':
		case '#':
			playerMove(newPosition, user, level->tiles);
			break;
		case 'X':
		case 'G':
		case 'T':
			combat(user, getMonsterAt(newPosition, level->monsters), 1);
			break;
		default:
			//move(user->position->y, user->position->x);
			break;
	}
}
