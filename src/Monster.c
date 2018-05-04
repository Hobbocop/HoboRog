#include "rog.h"

/*#############################################################################
#	MONSTER FUNCTIONS
#############################################################################*/

int addMonsters(Level * level)
{
	int x;
	level->monsters = malloc(sizeof(Monster*)*6);
	level->numberOfMonsters = 0;

	srand(time(NULL));


	for(x = 0; x<level->numberOfRooms;x++)
	{
		if(TRUE)//if((rand()%50)>=1)
		{
			level->monsters[level->numberOfMonsters] = selectMonster(level->lvl);
			setStartingPosition(level->monsters[level->numberOfMonsters], level->rooms[x]);
			level->numberOfMonsters++;
		}
	}

	//move(level->user->position->y, level->user->position->x);
}

//Used for monster generation, selects one type of monster to create
Monster * selectMonster(int floorLevel)
{
	int monsterType;

	switch(floorLevel)
	{
		case 0:
		case 1:
		case 2:
		case 3:
			monsterType = (rand()%2) + 1;
			break;
		case 4:
		case 5:
			monsterType = (rand()%2) + 2;
			break;
		case 6:
			monsterType = 3;
			break;
	}

	switch(monsterType)
	{
		case 0:
		case 1: //Spider
			return createMonster('X', 2,1,1,1,1, "Spider", 5);
		case 2:	//Goblin
			return createMonster('G', 5,2,1,1,0, "Goblin", 25);
		case 3: //Troll
			return createMonster('T',15,5,1,1,1, "Troll", 125);
	}
}

//Used for monster generation, creates and initializes structs to keep track of monsters
Monster* createMonster(char symbol, int health, int attack,
	int speed, int defense, int pathfinding, char* type, int xp)
{
	Monster* newMonster;
	newMonster = malloc(sizeof(Monster));
	newMonster->symbol=symbol;
	sprintf(newMonster->string, "%c", newMonster->symbol);
	newMonster->hp=health;
	newMonster->attack=attack;
	newMonster->speed=speed;
	newMonster->defense=defense;
	newMonster->pathfinding=pathfinding;
	newMonster->type = type;
	newMonster->alive=1;
	newMonster->exp=xp;
}

//Sets the monster alive flag to FALSE
int killMonster(Monster* monster)
{
	monster->alive = 0;
	return 0;
}

//Spawn the monster randomly inside the room
int setStartingPosition(Monster* monster, Room* room)
{
	monster->position = malloc(sizeof(Coords));
	monster->position->y = (rand() % (room->height-2)) + room->coords.y +2 ;
	monster->position->x = (rand() % (room->width-2)) + room->coords.x +2 ;
}

//Moves all monster according to their preffered algorithm
int moveMonsters(Level* level)
{
	int x;
	int move = 0;


	for(x=0; x<level->numberOfMonsters; x++)
	{
		if (level->monsters[x]->alive == 0)
			continue;

		if(level->monsters[x]->pathfinding == PATHFINDING_RANDOM)
		{
			pathfindingRandom(level->monsters[x]->position, level->user->position, level->tiles);
		}

		else if(level->monsters[x]->pathfinding == PATHFINDING_SEEK)
		{
			move = pathfindingSeek(level->monsters[x]->position, level->user->position, level->tiles);
		}

		if(move == 2)
		{
			combat(level->user, level->monsters[x], 0);
		}
	}
	return 1;
}

//Draws the monster on the screen, utilitiy function
int drawMonster(Monster* monster)
{
	mvprintw(monster->position->y, monster->position->x, monster->string);
}

//return 0 if coordinates (y1,x1) and (y2,x2) collide collide
int checkCoordCollision(int y1, int x1, int y2, int x2)
{
	return (y1!=y2 || x1 != x2);
}

//Moves the coordinate/position on step closer to the destination,
// returns 2 if monster catches player, -1 if monster can't move
int pathfindingSeek(Coords* start, Coords* destination, char ** tiles)
{
	//Take a step, if closer and empty --- store new coords

	//step left
	if((abs((start->x-1) - destination->x) < abs(start->x-destination->x))
	&& validTileMove(start->y,start->x-1, tiles)) //Make sure it's a valid space
	{
		if(checkCoordCollision(start->y,start->x-1,destination->y,destination->x))
			start->x = start->x-1;
		else
			return 2;	//Combat time!
	}
	//step right
	else if((abs((start->x+1) - destination->x) < abs(start->x-destination->x))
	&& validTileMove(start->y,start->x+1, tiles))
	{
		if(checkCoordCollision(start->y,start->x+1,destination->y,destination->x))
			start->x = start->x+1;
		else
			return 2;	//Combat time!
	}
	//step down
	else if((abs((start->y+1) - destination->y) < abs(start->y-destination->y))
	&& validTileMove(start->y+1,start->x, tiles)
	/*&& (mvinch(start->y+1, start->x) == '.')*/)
	{
		if(checkCoordCollision(start->y+1,start->x,destination->y,destination->x))
			start->y = start->y+1;
		else
			return 2;
	}
	//step up
	else if((abs((start->y-1) - destination->y) < abs(start->y-destination->y))
	&& validTileMove(start->y-1,start->x, tiles))
	{
		if(checkCoordCollision(start->y-1,start->x,destination->y,destination->x))
			start->y = start->y-1;
		else
			return 2;
	}
	else
	{	//Could not make a valid move, stuck against a wall
		return -1;
	}
}

//Moves the coordinate/position one step in a 'random' direction
int pathfindingRandom(Coords* position, Coords* target, char ** tiles)
{
	int random = (rand()%5);

	switch(random)
	{
		//Step up
		case 0:
			if (validTileMove(position->y-1,position->x, tiles))
			{
				//Check to see that we aren't stepping on the user
				if(checkCoordCollision(position->y-1,position->x,target->y,target->x))
					position->y = position->y-1;
				else
					return 2; //MORTAL COMBAT
			}
			break;
		//Step down
		case 1:
			if (validTileMove(position->y+1,position->x, tiles))
			{
				if(checkCoordCollision(position->y+1,position->x,target->y,target->x))
					position->y = position->y+1;
				else
					return 2; //MORTAL COMBAT
			}
			break;
		//Step left
		case 2:
			if (validTileMove(position->y,position->x-1, tiles))
			{
				if(checkCoordCollision(position->y,position->x-1,target->y,target->x))
					position->x = position->x-1;
				else
					return 2; //MORTAL COMBAT
			}
			break;
		//Step right
		case 3:
			if (validTileMove(position->y,position->x+1, tiles))
			{
				if(checkCoordCollision(position->y,position->x+1,target->y,target->x))
					position->x = position->x+1;
				else
					return 2; //MORTAL COMBAT
			}
			break;
		//No step
		case 4:
			break;
	}
}

//Returns the monster struct that is at the given coord
Monster* getMonsterAt(Coords position, Monster** monsters)
{
	int x;
	for(x=0;x<6;x++)
	{
		if((position.y  == monsters[x]->position->y)
		&& (position.x  == monsters[x]->position->x))
			return monsters[x];
	}
}
/**
*
*	struct Monster
*	{
*		Coords position;
*		char symbol;	//Represent what type of monstor
*		int hp;
*		int attack;
*		int speed;		//Probably only going to be 1
*		int defense;
*		int pathfinding;//How does the monster use? 0 - Seeking, 1 - random
*
*	} Monster;
*
*	Monster stat cheat sheet
*
*
*	1 Spiders
*		symbol:		"x"
*		Lvl: 	1-3
*		hp: 		2
*		attack: 	1
*		speed: 		1
*		defense:	1
*		Pathfind:	1 (random)
*
*	2 Goblin
*		Symbol:		"G"
*		Lvl: 	1-5
*		hp: 		5
*		attack: 	3
*		speed: 		1
*		defense:	1
*		Pathfind:	0 (seeking)
*
*
*	3 Troll
*		Symbol:		"T"
*		Lvl: 	4-6
*		hp: 		15
*		attack: 	5
*		speed: 		1
*		defense:	1
*		Pathfind:	1 (random)
*
*	TODO - Add more monstros
*
**/