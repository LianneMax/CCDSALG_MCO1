#include "sort.h"
#include <math.h>
#include <stdio.h> // For standard I/O functions

// Helper function to calculate the polar angle between a point and the anchor
double polarAngle(Coord p1, Coord anchor) {
    return atan2(p1.y - anchor.y, p1.x - anchor.x);
}

// Slow Sorting Algorithm: Selection Sort
void selectSort(int n, Coord points[], Coord anchor) {
    int i, j, minIdx;
    Coord temp;

    for (i = 0; i < n - 1; i++) {
        minIdx = i;
        for (j = i + 1; j < n; j++) {
            // Compare points based on polar angle with respect to the anchor
            if (polarAngle(points[j], anchor) < polarAngle(points[minIdx], anchor)) {
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

// Heapify function for Heap Sort
void heapify(Coord points[], int n, int i, Coord anchor) {
    int largest = i;        // Initialize largest as root
    int left = 2 * i + 1;   // Left child
    int right = 2 * i + 2;  // Right child

    // If left child is larger based on polar angle
    if (left < n && polarAngle(points[left], anchor) > polarAngle(points[largest], anchor)) {
        largest = left;
    }

    // If right child is larger based on polar angle
    if (right < n && polarAngle(points[right], anchor) > polarAngle(points[largest], anchor)) {
        largest = right;
    }

    // If largest is not root, swap and heapify recursively
    if (largest != i) {
        swap(&points[i], &points[largest]);
        heapify(points, n, largest, anchor);
    }
}

// Fast Sorting Algorithm: Heap Sort
void heapSort(Coord points[], int n, Coord anchor) {
    // Build the heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(points, n, i, anchor);
    }

    // Extract elements from the heap
    for (int i = n - 1; i > 0; i--) {
        // Move the root of the heap to the end
        swap(&points[0], &points[i]);

        // Call heapify on the reduced heap
        heapify(points, i, 0, anchor);
    }
}
