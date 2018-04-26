#include "rog.h"
#include "utils.h"

/*#############################################################################
#	LEVEL FUNCTIONS
#############################################################################*/
//Create a struct for a lvl level allocating standard values
Level * createLevel(int lvl)
{
	Level * newLevel;
	newLevel = malloc(sizeof(Level));
	newLevel->lvl = lvl;
	newLevel->numberOfRooms = 6;
	newLevel->rooms = roomsSetup();
	newLevel->tiles=saveLevelPositions();
	newLevel->user = playerSetUp();
	placePlayer(newLevel->rooms, newLevel->user);

	addMonsters(newLevel);

	return newLevel;
}

//Creates maps and and sends them to be drawn on the map
Room** roomsSetup()
{
	int x;
	Room** rooms;
	rooms = malloc(sizeof(Room)*6);

	//OBS- createRoom(x,y,_,_)
	//	 - mvpritw(y,x,_)
	//   - care about the order of x and y!

	for(x=0; x<6; x++)
	{
		srand(time(NULL));
		rooms[x] = createRoom(x);
		drawRoom(rooms[x]);
	}

	pathFind(rooms[0]->door[3], rooms[4]->door[2]);
	//Create paths, hardcoded for now
	/*
	connectDoors(rooms[1]->door[2], rooms[0]->door[0]);
	connectDoors(rooms[0]->door[3], rooms[2]->door[2]);
	connectDoors(rooms[1]->door[1], rooms[2]->door[0]);
	*/
	return rooms;
}

char ** saveLevelPositions()
{
	int x, y;

	char ** positions;
	positions = malloc((sizeof(char*))*GLOBAL_MAX_HEIGHT);

	for(y = 0; y<25; y++)
	{
		positions[y] = malloc(sizeof(char) * GLOBAL_MAX_WIDTH);
		for (x = 0; x<100; x++)
		{
			positions[y][x] = mvinch(y,x);
		}
	}

	return positions;
}