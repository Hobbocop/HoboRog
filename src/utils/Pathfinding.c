#include "rog.h"
#include "utils.h"

void addPositionYX(int** frontier, int frontierCount, int y, int x)
{
	frontier[frontierCount][0] = y;
	frontier[frontierCount][1] = x;
}

int checkNeighbour(int y, int x)
{
	char temp = mvinch(y,x);

	if(temp == '.' || temp=='|' || temp=='+' || temp == '-')
		return FALSE;
	else
		return TRUE;
}

int addNeighbours(int** frontier, int frontierCount, int*** cameFrom, int y, int x)
{
	//North Neighbour
	//There exist a unvisited neighbor to the north
	if(y > 0 && cameFrom[y-1][x][0] < 0 && checkNeighbour(y-1,x))
	{
		//Expand frontier by adding this element
		addPositionYX(frontier, frontierCount, y-1, x);

		//Increment counter
		frontierCount++;

		//Save the breadcrumbs how we got to this position
		cameFrom[y-1][x][0] = y;
		cameFrom[y-1][x][1] = x;
	}

	//South Neighbour
	//There exist a unvisited neighbor to the south
	if(y < (GLOBAL_MAX_HEIGHT-1) && cameFrom[y+1][x][0] < 0 && checkNeighbour(y+1,x))
	{
		addPositionYX(frontier, frontierCount, y+1, x);
		frontierCount++;
		cameFrom[y+1][x][0] = y;
		cameFrom[y+1][x][1] = x;
	}

	//West Neighbour
	//There exist a unvisited neighbor to the west
	if(x > 0 && cameFrom[y][x-1][0] < 0 && checkNeighbour(y,x-1))
	{
		addPositionYX(frontier, frontierCount, y, x-1);
		frontierCount++;
		cameFrom[y][x-1][0] = y;
		cameFrom[y][x-1][1] = x;
	}

	//East Neighbour
	//There exist a neighbor to the east
	if(x < (GLOBAL_MAX_WIDTH-1) && cameFrom[y][x+1][0] < 0 && checkNeighbour(y,x+1))
	{
		addPositionYX(frontier, frontierCount, y, x+1);
		frontierCount++;
		cameFrom[y][x+1][0] = y;
		cameFrom[y][x+1][1] = x;
	}

	return frontierCount;
}

void pathFind(Coords* start, Coords* end)
{
	//Variables
	int i, j;	//Index counters
	int x, y;	//Temp variables for coords
	int tempY, tempX;
	int frontierIndex = 0;
	int frontierCount = 0;
	int** frontier = malloc(sizeof(int*) * (GLOBAL_MAX_HEIGHT * GLOBAL_MAX_WIDTH));
	int*** cameFrom = malloc(sizeof(int**) * GLOBAL_MAX_HEIGHT);

	//Make space for frontier
	for(i = 0; i < GLOBAL_MAX_WIDTH * GLOBAL_MAX_HEIGHT; i++)
	{
		frontier[i]= malloc(sizeof(int)*2);
	}

	//Make space for cameFrom
	for (i = 0; i < GLOBAL_MAX_HEIGHT; i++)
	{
		cameFrom[i] = malloc(sizeof(int*)*GLOBAL_MAX_WIDTH);
		for(j = 0; j< GLOBAL_MAX_WIDTH; j++)
		{
			cameFrom[i][j] = malloc(sizeof(int)*2);
			cameFrom[i][j][0] = -1;
			cameFrom[i][j][1] = -1;
		}
	}

	//add start to cameFrom
	cameFrom[start->y][start->x][0] = -9; //(-9,-9) arbitrary start value
	cameFrom[start->y][start->x][1] = -9;

	//Add position to the frontier
	addPositionYX(frontier, frontierCount, start->y, start->x);
	frontierCount++;

	//Find the end position through BFS, keep track of how we got there
	while(frontierIndex < frontierCount)
	{
		//Load current index coordinate
		y = frontier[frontierIndex][0];
		x = frontier[frontierIndex][1];

		//If we found the position, break out of the while loop
		if(y==end->y && x==end->x)
		{
			break;
		}

		//Otherwise, increment the index we're checking
		frontierIndex++;

		//Add all the neightbours to (y,x) to the frontier and track how many we added
		frontierCount = addNeighbours(frontier, frontierCount, cameFrom, y, x);
	}

	y = end->y;
	x = end->x;

	//Backtrack along the trail of crumbs
	while(y!=start->y || x!= start->x)
	{
		tempY = y;
		tempX = x;
		y = cameFrom[tempY][tempX][0];
		x = cameFrom[tempY][tempX][1];

		mvprintw(y,x,"#");
		//getch();
	}
}