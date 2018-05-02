//Guard against multiple includes, to make sure no unnessecary lines of code
#ifndef ROGUE_H
#define ROGUE_H

#include <ncurses/ncurses.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

#define PATHFINDING_RANDOM 1
#define PATHFINDING_SEEK 0


/*#############################################################################
#	Structs
#############################################################################*/
//Struct to make coordinates easier to handle;
typedef struct Coords
{
	int x;
	int y;
	//TILE_TYPE tile;	--- MAYBE
} Coords;

//Struct to keep track of player data and stats
typedef struct Player
{
	Coords* position;
	int hp;
	int attack;
	int defense;
	int exp;
	int lvl;
	int gold;
	int maxHp;
	//Room * room;	// Keep track of room that player is in
} Player;

//Struct to keep track of room data (coords) and stats
typedef struct Room
{
	Coords coords;	//X and Y coords of the top left corner
	//Coords** door;
	int height;
	int width;
	int numberOfDoors;
	struct Door** door;

	// TODO - Create structs for monsters and items
	//Monster** monsters;
	//Item** items;
} Room;

//Struct to keep track of Doors, basically two Coords
typedef struct Door
{
	int connected;
	Coords entrance;
	Coords exit;
} Door;

//Struct to keep track of level data (rooms) and stats
typedef struct level
{
	char ** tiles;
	int lvl;
	int numberOfRooms;
	int numberOfMonsters;
	struct Room** rooms;
	struct Monster** monsters;
	struct Player* user;
} Level;

//Struct to keep track of monster
typedef struct Monster
{
	Coords* position;
	char symbol;	//Represent what type of monstor
	char string[2];
	char* type;
	int hp;
	int attack;
	int speed;		//Probably only going to be 1
	int defense;
	int pathfinding;//How does the monster use? 0 - Seeking, 1 - random
	int alive;		//1-yes, 0-no
	int exp;
} Monster;

/*#############################################################################
#	GLOBAL VARIABLES
#############################################################################*/
//Generally frowned upon, but these will be constant after having been set once
int GLOBAL_MAX_HEIGHT;
int GLOBAL_MAX_WIDTH;


/*#############################################################################
#	Functions
#############################################################################*/

//Screen functions - Screen.c
int screenSetUp();
void printFrame();
void printInnerFrame();
int printGameHud(Level* level);

//Level/Map functions - Level.c
Level * createLevel(int lvl);
void drawLevel(Level* level);
Room** roomsSetup();
char** saveLevelPositions();
void connectDoors(Level* level);
int validTileMove(int x, int y, char** tiles);

//Room functions - Rooms.c
Room* createRoom(int grid, int numberOfDoors);
int drawRoom(Room* room);
//int connectDoors(Coords doorOne, Coords doorTwo);

//Input and movement functions - Player.c
Coords handleInput(int input, Player* user);
int checkPosition(Coords newPosition, Level* level);
Player* playerSetUp();
int placePlayer(Room** rooms, Player* user);
int playerMove(Coords newPosition, Player* user, char ** level);
int addExp(Player* user, int xp);
int levelUp(Player* user);
void drawPlayer(Player* user);

//Monster functions - Monster.c
int addMonsters(Level * level);
Monster * selectMonster(int floorLevel);
Monster* createMonster(char symbol, int health, int attack, int speed, int defense, int pathfinding, char* type, int xp);
int killMonster(Monster* monster);
int setStartingPosition(Monster* monster, Room* room);
int moveMonsters(Level* level);
int drawMonster(Monster* monster);
int pathfindingSeek(Coords* start, Coords* destination, char ** tiles);
int pathfindingRandom(Coords* position, Coords* target, char ** tiles);
Monster* getMonsterAt(Coords position, Monster** monsters);

//Combat functions - Combat.c
int combat(Player* player, Monster* monster, int order);




#endif