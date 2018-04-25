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

int placePlayer(Room** rooms, Player* user)
{
	user->position->x = rooms[3]->coords.x+1;
	user->position->y = rooms[3]->coords.y+1;

	mvprintw(user->position->y, user->position->x, "@");
	move(user->position->y, user->position->x);
}

//Moves the player character to the new x and y
int playerMove(Coords newPosition, Player* user, char ** level)
{

	char buffer[8];

	//level[user->position.y][user->position.x];

	sprintf(buffer, "%c", level[user->position->y][user->position->x]);

	mvprintw(user->position->y, user->position->x, buffer);

	user->position->y = newPosition.y;
	user->position->x = newPosition.x;

	mvprintw(user->position->y, user->position->x, "@");
	move(user->position->y, user->position->x);
}

//Increments the experience counter, also signals when levelup
int addExp(Player* player, int xp)
{
	player->exp += xp;
	if(xp>=5 && player->lvl==1)
		levelUp(player);
	return 1;
}

//Increments the players level and stats accordingly
int levelUp(Player* player)
{
	mvprintw(2,0, "Level up! Stats have been increased!");
	player->attack++;
	player->maxHp+=10;
	player->hp = player->maxHp;
	player->lvl++;
	return 1;
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
			newPosition.y = user->position->y-1;
			newPosition.x = user->position->x;
			break;

		//Move left
		case 'a':
		case 'A':
			newPosition.y = user->position->y;
			newPosition.x = user->position->x-1;
			break;

		//Move down
		case 's':
		case 'S':
			newPosition.y = user->position->y+1;
			newPosition.x = user->position->x;
			break;

		//Move right
		case 'd':
		case 'D':
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
			move(user->position->y, user->position->x);
			break;
	}
}
