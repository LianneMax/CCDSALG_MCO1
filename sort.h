#define STACK_H    // Define STACK_H if it isn't defined
#define MAX 32768

#include <stdio.h>
#include "stack.h"

typedef struct 
{
	double x, y;
} Coord;

double polarAngle(Coord p1, Coord p2, Coord anchor);
void selectSort(int n, Coord points[], Coord anchor);
void heapSort( points[], int n, Coord p0);