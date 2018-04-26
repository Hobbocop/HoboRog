#ifndef UTILS_H
#define UTILS_H

/*#############################################################################
#	Functions
#############################################################################*/

//Pathfinding functions - Pathfinding.c
void addPositionYX(int** frontier, int frontierCount, int y, int x);
int addNeighbours(int** frontier, int frontierCount, int*** cameFrom, int y, int x);
void pathFind(Coords* start, Coords* end);
#endif
