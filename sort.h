#ifndef STACK_H    // Check if STACK_H is not defined
#define STACK_H    // Define STACK_H if it isn't defined
#include <stdio.h>
#define MAX 37268
#include "stack.h"

typedef struct 
{
	double x, y;
} Coord;

double polarAngle(Coord p1, Coord p2, Coord anchor);
void selectSort(int n, Coord points[], Coord anchor);
void heapSort(Coord points[], int n, Coord p0);

#endif