#include "sort.h"
#include <stdio.h> // For standard I/O functions


// Helper function to swap two points
void swap(Coord* a, Coord* b) {
    Coord temp = *a;
    *a = *b;
    *b = temp;
}
// Helper function to compare points based on cross product (avoiding atan2)
// Determines the order of points relative to an anchor point.
// Returns -1 if p1 is counterclockwise to p2, 1 if clockwise, 0 if collinear.
int compareByPolarAngle(const Coord* p1, const Coord* p2, Coord anchor) {
    // Calculate cross product to determine orientation
    double cross_product = (p1->x - anchor.x) * (p2->y - anchor.y) - (p1->y - anchor.y) * (p2->x - anchor.x);

    // Determine if points are counterclockwise, clockwise, or collinear
    if (cross_product > 0) {
        return -1;    // p1 is counterclockwise to p2
    }
    if (cross_product < 0) {
        return 1;     // p2 is counterclockwise to p1
    }

    // If points are collinear, sort by distance to the anchor
    double dist1 = (p1->x - anchor.x) * (p1->x - anchor.x) + (p1->y - anchor.y) * (p1->y - anchor.y);
    double dist2 = (p2->x - anchor.x) * (p2->x - anchor.x) + (p2->y - anchor.y) * (p2->y - anchor.y);
    
    if (dist1 < dist2) {
        return -1;    // p1 is closer to the anchor than p2
    } else {
        return 1;     // p2 is closer to the anchor than p1, or they are equidistant
    }
}

// Selection Sort (slow sorting algorithm) using cross product to order points by polar angle
// Sorts points based on polar angle relative to an anchor point using selection sort.
void selectSort(int n, Coord points[], Coord anchor) {
    int i, j, minIdx;  // Loop variables
    Coord temp; // Temporary variable for swapping points

    for (i = 0; i < n - 1; i++) {
        minIdx = i;  // Start with the current element as the minimum
        for (j = i + 1; j < n; j++) {
            // Update minimum index if a smaller polar angle is found
            if (compareByPolarAngle(&points[j], &points[minIdx], anchor) < 0) {
                minIdx = j;
            }
        }

        swap(&points[i], &points[minIdx]);
        /*
        // Swap the found minimum element with the current element
        temp = points[i];
        points[i] = points[minIdx];
        points[minIdx] = temp;
        */
    }
}
/*
// Helper function to swap two points
void swap(Coord* a, Coord* b) {
    Coord temp = *a;
    *a = *b;
    *b = temp;
}
*/
// Heapify function for Heap Sort
// Ensures the max-heap property is maintained by comparing parent and child nodes based on polar angle
void heapify(Coord points[], int n, int i, Coord anchor) {
    int largest = i;        // Assume the largest element is the root
    int left = 2 * i + 1;   // Index of left child
    int right = 2 * i + 2;  // Index of right child

    // Compare root with left child and update largest if left child is greater
    if (left < n && compareByPolarAngle(&points[left], &points[largest], anchor) > 0) {
        largest = left;
    }

    // Compare largest with right child and update if right child is greater
    if (right < n && compareByPolarAngle(&points[right], &points[largest], anchor) > 0) {
        largest = right;
    }

    // If largest is not the root, swap and recursively heapify the affected subtree
    if (largest != i) {
        swap(&points[i], &points[largest]);
        heapify(points, n, largest, anchor);
    }
}

// Heap Sort (fast sorting algorithm) based on polar angle relative to the anchor point
// Sorts points using a heap to ensure efficient ordering for Graham's scan
void heapSort(Coord points[], int n, Coord anchor) {
    int i;  // Loop variable

    // Build max-heap by calling heapify on all non-leaf nodes from the bottom up
    for (i = n / 2 - 1; i >= 0; i--) {
        heapify(points, n, i, anchor);
    }

    // Extract elements from the heap one by one and place them in sorted order
    for (i = n - 1; i > 0; i--) {
        // Move the root of the heap to the end of the sorted array
        swap(&points[0], &points[i]);
        // Call heapify on the reduced heap
        heapify(points, i, 0, anchor);
    }
}
