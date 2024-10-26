#include "sort.h"
#include <stdio.h> // For standard I/O functions

// Helper function to compare points based on cross product (avoiding atan2)
int compareByPolarAngle(const Coord* p1, const Coord* p2, Coord anchor) {
    double cross_product = (p1->x - anchor.x) * (p2->y - anchor.y) - (p1->y - anchor.y) * (p2->x - anchor.x);
    if (cross_product > 0) return -1;    // p1 is counterclockwise to p2
    if (cross_product < 0) return 1;     // p2 is counterclockwise to p1
    // If collinear, sort by distance to the anchor
    double dist1 = (p1->x - anchor.x) * (p1->x - anchor.x) + (p1->y - anchor.y) * (p1->y - anchor.y);
    double dist2 = (p2->x - anchor.x) * (p2->x - anchor.x) + (p2->y - anchor.y) * (p2->y - anchor.y);
    return dist1 < dist2 ? -1 : 1;
}

// Slow Sorting Algorithm: Selection Sort (using cross product)
void selectSort(int n, Coord points[], Coord anchor) {
    int i, j, minIdx;  // Declare variables outside the loop
    Coord temp;

    for (i = 0; i < n - 1; i++) {
        minIdx = i;
        for (j = i + 1; j < n; j++) {
            if (compareByPolarAngle(&points[j], &points[minIdx], anchor) > 0) {
                minIdx = j;
            }
        }
        // Swap the found minimum element with the first element
        temp = points[i];
        points[i] = points[minIdx];
        points[minIdx] = temp;
    }
}

// Swap function used by heap sort
void swap(Coord* a, Coord* b) {
    Coord temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify function for Heap Sort (using cross product comparison)
void heapify(Coord points[], int n, int i, Coord anchor) {
    int largest = i;        // Initialize largest as root
    int left = 2 * i + 1;   // Left child
    int right = 2 * i + 2;  // Right child

    if (left < n && compareByPolarAngle(&points[left], &points[largest], anchor) < 0) {
        largest = left;
    }

    if (right < n && compareByPolarAngle(&points[right], &points[largest], anchor) < 0) {
        largest = right;
    }

    if (largest != i) {
        swap(&points[i], &points[largest]);
        heapify(points, n, largest, anchor);
    }
}

// Fast Sorting Algorithm: Heap Sort (using cross product)
void heapSort(Coord points[], int n, Coord anchor) {
    int i;  // Declare 'i' here for both loops

    // Build the heap
    for (i = n / 2 - 1; i >= 0; i--) {  // Use 'i' declared above
        heapify(points, n, i, anchor);
    }

    // Extract elements from the heap
    for (i = n - 1; i > 0; i--) {  // Reuse 'i'
        swap(&points[0], &points[i]);
        heapify(points, i, 0, anchor);
    }
}

