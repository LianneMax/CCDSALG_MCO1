#ifndef SORT_H
#define SORT_H

#include "stack.h" // Include the stack header for the Coord type definition

// Declaration of the Selection Sort function
// This function performs selection sort on an array of points based on their polar angle
// relative to a specified anchor point. It is intended to be used in the slow version
// of Graham's Scan.
void selectSort(int n, Coord points[], Coord anchor);

// Declaration of the Heap Sort function
// This function performs heap sort on an array of points based on their polar angle
// relative to a specified anchor point. It is intended to be used in the fast version
// of Graham's Scan.
void heapSort(Coord points[], int n, Coord anchor);

#endif // End of SORT_H
