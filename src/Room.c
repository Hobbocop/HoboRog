#include "rog.h"


/*#############################################################################
#	ROOM FUNCTIONS
#############################################################################*/
//Initialises roooms and allocates memory
Room* createRoom(int grid, int numberOfDoors)
{
	srand(time(NULL)+grid);

	int i;
	Room * newRoom;
	newRoom = malloc(sizeof(Room));
	newRoom->numberOfDoors = numberOfDoors;

	//Based on which grid the room is on, it's going to have different coords
	switch(grid)
	{
		case 0:
			newRoom->coords.x=0;
			newRoom->coords.y=1;
			break;
		case 1:
			newRoom->coords.x=33;
			newRoom->coords.y=1;
			break;
		case 2:
			newRoom->coords.x=66;
			newRoom->coords.y=1;
			break;
		case 3:
			newRoom->coords.x=1;
			newRoom->coords.y=14;
			break;
		case 4:
			newRoom->coords.x=33;
			newRoom->coords.y=14;
			break;
		case 5:
			newRoom->coords.x=66;
			newRoom->coords.y=14;
			break;
	}

	newRoom->height = (rand()%6) +4; //Max height 9
	newRoom->width = (rand()%15) +4; //Max width 19

	//Offset for the room position
	newRoom->coords.x += (rand()%(30-newRoom->width));
	newRoom->coords.y += (rand()%(10-newRoom->height));


	newRoom->door = malloc(sizeof(Coords)*numberOfDoors);

	for(i = 0; i < numberOfDoors; i++)
	{
		newRoom->door[i] = malloc(sizeof(Door));
		newRoom->door[i] = 0;
	}



	srand(time(NULL)+grid);
	//A door at the top of the room
	newRoom->door[0]->entrance.x = 1 + rand() % (newRoom->width - 2) + newRoom->coords.x;
	newRoom->door[0]->entrance.y = newRoom->coords.y;

	srand(time(NULL)+12+grid);
	//A door at the bottom of the room
	newRoom->door[1]->entrance.x = 1 + rand() % (newRoom->width - 2) + newRoom->coords.x;
	newRoom->door[1]->entrance.y = newRoom->coords.y + newRoom->height;

	srand(time(NULL)+31);
	//Left door
	newRoom->door[2]->entrance.x = newRoom->coords.x;
	newRoom->door[2]->entrance.y = 1 + rand() % (newRoom->height -2) + newRoom->coords.y;

	srand(time(NULL)+42-grid);
	//Right door
	newRoom->door[3]->entrance.x = newRoom->coords.x+ newRoom->width;
	newRoom->door[3]->entrance.y = 1 + rand() % (newRoom->height -2) + newRoom->coords.y;

	return newRoom;
}

//Draws a room in the window
int drawRoom(Room* room)
{
	int x;
	int y;
	int i;

	int topY = room->coords.y;
	int botY = room->coords.y + room->height;

	int leftX = room->coords.x;
	int rightX = room->coords.x + room->width;

	// draw top and bottom
	for(x = leftX; x < rightX; x++)
	{
		mvprintw(topY, x, "-");
		mvprintw(botY, x, "-");
	}

	// Draw walls and floor
	for(y = topY+1; y< botY; y++)
	{
		//Draw Wall
		mvprintw(y, leftX, "|");
		mvprintw(y, rightX, "|");

		//Draw floor
		for(x=leftX+1; x < rightX; x++)
		{
			mvprintw(y, x, ".");
		}
	}

	//Draw corners
	mvprintw(room->coords.y,room->coords.x,"+");
	mvprintw(room->coords.y+room->height,room->coords.x,"+");
	mvprintw(room->coords.y+room->height,room->coords.x+room->width,"+");
	mvprintw(room->coords.y,room->coords.x+room->width,"+");

	//Draw doors
	for(i=0; i<4; i++)
	{
		mvprintw(room->door[i]->entrance.y, room->door[i]->entrance.x, "#");
	}
	return 1;
}

//Draws pathway between coordinates/doors
int connectDoors(Coords doorOne, Coords doorTwo)
{
	Coords temp;
	Coords prev;

	int count = 0;
	int step; //0 - left, 1 - right, 2 - down, 3 - up, 4 - n/A

	temp.x = doorOne.x;
	temp.y = doorOne.y;

	prev = temp;

	while(TRUE)
	{
		//Take a step, if closer and empty --- store new coords

		//step left
		if((abs((temp.x-1) - doorTwo.x) < abs(temp.x-doorTwo.x)) && (mvinch(temp.y, temp.x-1) == ' '))
		{
			step = 0;
			prev.x = temp.x;
			temp.x = temp.x-1;
		}
		//step right
		else if((abs((temp.x+1) - doorTwo.x) < abs(temp.x-doorTwo.x)) && (mvinch(temp.y, temp.x+1) == ' '))
		{
			step = 1;
			prev.x = temp.x;
			temp.x = temp.x+1;
		}
		//step down
		else if((abs((temp.y+1) - doorTwo.y) < abs(temp.y-doorTwo.y)) && (mvinch(temp.y+1, temp.x) == ' '))
		{
			step = 2;
			prev.y = temp.y;
			temp.y = temp.y+1;
		}
		//step up
		else if((abs((temp.y-1) - doorTwo.y) < abs(temp.y-doorTwo.y)) && (mvinch(temp.y-1, temp.x) == ' '))
		{
			step = 3;
			prev.y = temp.y;
			temp.y = temp.y-1;
		}
		//Hit a snag,
		else
		{
			//Are we there?
			if((temp.x == doorTwo.x) && (temp.y+1 == doorTwo.y))
				return 1;
			else if((temp.x == doorTwo.x) && (temp.y-1 == doorTwo.y))
				return 1;
			else if((temp.x+1 == doorTwo.x) && (temp.y == doorTwo.y))
				return 1;
			else if((temp.x-1 == doorTwo.x) && (temp.y == doorTwo.y))
				return 1;

			//Then backtrack
			else if(count == 0)
			{
				//mvprintw(2,0, "!Prev(%d,%d): \'%c\', temp(%d,%d): \'%c\'", prev.y,prev.x,mvinch(prev.y,prev.x), temp.y,temp.x,mvinch(temp.y,temp.x));
				temp = prev;
				count++;
				continue;
			}

			//Already backtracked once, I'm lost
			else
			{
				return 0;
			}
		}

		//mvprintw(1,0, "Prev(%d,%d): \'%c\', temp(%d,%d): \'%c\'", prev.y,prev.x,mvinch(prev.y,prev.x), temp.y,temp.x,mvinch(temp.y,temp.x));
		//getch();
		mvprintw(temp.y, temp.x, "#");
	}
	return 1;
}
