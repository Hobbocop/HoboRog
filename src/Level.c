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
	connectDoors(newLevel);
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
		rooms[x] = createRoom(x, 4);
		drawRoom(rooms[x]);
	}

	return rooms;
}

void connectDoors(Level* level)
{
	int i, j;
	int randomRoom, randomDoor;
	int count;

	//Loop through all Rooms
	for(i=0; i < level->numberOfRooms; i++)
	{
		//Loop through all doors
		for(j=0; j< level->rooms[i]->numberOfDoors; j++)
		{
			//Check to ensure door isn't connected already
			if(level->rooms[i]->door[j]->connected == 1)
				continue;

			count = 0;

			while(count < 20)
			{
				randomRoom = (rand() % level->numberOfRooms);
				randomDoor = (rand() % level->rooms[randomRoom]->numberOfDoors);

				//Ceck to ensure tha the random door chosen isn't connected already
				if(level->rooms[randomRoom]->door[randomDoor]->connected == 1 || randomRoom == i)
				{
					count++;
					continue;
				}

				//Connect the doors
				pathFind(&level->rooms[randomRoom]->door[randomDoor]->entrance, &level->rooms[i]->door[j]->entrance);

				level->rooms[randomRoom]->door[randomDoor]->connected = 1;
				level->rooms[i]->door[j]->connected = 1;

				break;
			}
		}
	}
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