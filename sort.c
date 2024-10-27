#include "sort.h"
#include <stdio.h> // For standard I/O functions

// Helper function to compare points based on cross product (avoiding atan2)
// Using cross product instead of atan2 to avoid floating point inaccuracies
// Returns -1 if p1 is counterclockwise to p2, 1 if clockwise, 0 if collinear
int compareByPolarAngle(const Coord* p1, const Coord* p2, Coord anchor) {
    // Calculate cross product between vectors (anchor->p1) and (anchor->p2)
    double cross_product = (p1->x - anchor.x) * (p2->y - anchor.y) - (p1->y - anchor.y) * (p2->x - anchor.x);
    if (cross_product > 0) return -1;    // p1 is counterclockwise to p2
    if (cross_product < 0) return 1;     // p2 is counterclockwise to p1
    
    // If points are collinear (cross product == 0), sort by distance from the anchor point
    // And, sort by distance to the anchor
    double dist1 = (p1->x - anchor.x) * (p1->x - anchor.x) + (p1->y - anchor.y) * (p1->y - anchor.y);
    double dist2 = (p2->x - anchor.x) * (p2->x - anchor.x) + (p2->y - anchor.y) * (p2->y - anchor.y);
    return dist1 < dist2 ? -1 : 1;
}

// Slow Sorting Algorithm: Selection Sort (using cross product)
// Sorts points based on their polar angle relative to an anchor point
void selectSort(int n, Coord points[], Coord anchor) {
    int i, j, minIdx;  // Declare loop variables
    Coord temp;

    for (i = 0; i < n - 1; i++) {
        // Initialize minimum index as the first unsorted element
        minIdx = i;  
        for (j = i + 1; j < n; j++) {
            // Find the point with the smallest polar angle
            if (compareByPolarAngle(&points[j], &points[minIdx], anchor) < 0) {
                minIdx = j;
            }
        }
        // Swap the found minimum element with the current element
        temp = points[i];
        points[i] = points[minIdx];
        points[minIdx] = temp;
    }
}

// Helper function to swap two points
void swap(Coord* a, Coord* b) {
    Coord temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify function for Heap Sort
// Maintains the max-heap property by comparing parent and child nodes based on polar angle
void heapify(Coord points[], int n, int i, Coord anchor) {
    int largest = i;        // Initialize largest as the root node
    int left = 2 * i + 1;   // Left child index
    int right = 2 * i + 2;  // Right child index

    // Compare root with left child and update largest if left child is greater
    if (left < n && compareByPolarAngle(&points[left], &points[largest], anchor) < 0) {
        largest = left;
    }

    // Compare largest with right child and update if right child is greater
    if (right < n && compareByPolarAngle(&points[right], &points[largest], anchor) < 0) {
        largest = right;
    }

    // If largest is not the root, swap and recursively heapify the affected subtree
    if (largest != i) {
        swap(&points[i], &points[largest]);
        heapify(points, n, largest, anchor);
    }
}

// Fast Sorting Algorithm: Heap Sort
// Sorts points based on their polar angle relative to an anchor point
void heapSort(Coord points[], int n, Coord anchor) {
    int i;  // Loop variable

    // Build max-heap by calling heapify on all non-leaf nodes
    for (i = n / 2 - 1; i >= 0; i--) {  // Heapify from bottom up
        heapify(points, n, i, anchor);
    }

    // Extract elements from the heap one by one
    for (i = n - 1; i > 0; i--) {
        // Move the root of the heap to the end of the sorted array
        swap(&points[0], &points[i]);
        // Call heapify on the reduced heap
        heapify(points, i, 0, anchor);
    }
}