#ifndef SORT_H
#define SORT_H

#include "stack.h" // Include the stack header for Coord type

// Function to compare two points by polar angle with respect to an anchor point
// Returns -1 if p1 is counterclockwise to p2, 1 if clockwise, and 0 if collinear
int compareByPolarAngle(const Coord* p1, const Coord* p2, Coord anchor);

// Selection sort function based on polar angle relative to an anchor point
// Sorts points in ascending order of polar angle using selection sort
void selectSort(int n, Coord points[], Coord anchor);

// Heap sort function based on polar angle relative to an anchor point
// Sorts points in ascending order of polar angle using heap sort
void heapSort(Coord points[], int n, Coord anchor);

// Helper function for heap sort: heapifies a subtree rooted at index i
// Maintains the max-heap property with respect to the polar angle of points
void heapify(Coord points[], int n, int i, Coord anchor);

// Function to swap two points
// Used by sorting algorithms to swap points based on polar angle ordering
void swap(Coord* a, Coord* b);

#endif
