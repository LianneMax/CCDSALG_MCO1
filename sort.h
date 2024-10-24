#include <stdio.h>
#define MAX 37268


typedef struct 
{
	int x, y;
} Coord;


double polarAngle(Coord p1, Coord p2, Coord anchor);
void selectSort(int n, Coord points[], Coord anchor);

//done 
