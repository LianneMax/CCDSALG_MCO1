#ifndef SORT_H
#define SORT_H


#include "stack.h" // Include the stack header for Coord type

// Function declarations
void selectSort(int n, Coord points[], Coord anchor);
void heapSort(Coord points[], int n, Coord anchor);
double polarAngle(Coord p1, Coord anchor);

#endif