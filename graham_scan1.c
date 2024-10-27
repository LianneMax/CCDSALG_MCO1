// graham_scan1.c - Graham's Scan with Selection Sort (Slow Version)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"
#include "sort.h"

// Function to determine the orientation of three points
// Returns 0 if points are collinear, 1 if clockwise, 2 if counterclockwise
int orientation(Coord p, Coord q, Coord r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

// Graham's Scan using Selection Sort
Coord* grahamScan1(Coord points[], int n, int* hullSize) {
    int i;

    // Check if there are enough points to form a convex hull
    if (n < 3) {
        printf("Convex hull is not possible with less than 3 points.\n");
        *hullSize = 0;
        return NULL;
    }

    // Start timing for selection sort
    clock_t start = clock();

    // Step 1: Find the anchor point with the lowest y-coordinate (leftmost if tied)
    int minY = 0;
    for (i = 1; i < n; i++) {
        if (points[i].y < points[minY].y || (points[i].y == points[minY].y && points[i].x < points[minY].x)) {
            minY = i;
        }
    }

    // Move the anchor point to the first position
    Coord temp = points[0];
    points[0] = points[minY];
    points[minY] = temp;
    Coord p0 = points[0];

    // Step 2: Sort points by polar angle using selection sort
    selectSort(n, points, p0);

    // End timing and print elapsed time
    double timeElapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("Selection Sort took: %.6lf seconds\n", timeElapsed);

    // Step 3: Initialize the stack and add the first three points
    Stack s;
    createStack(&s, n);
    push(&s, points[0]);
    push(&s, points[1]);
    push(&s, points[2]);

    // Step 4: Process remaining points to construct the convex hull
    for (i = 3; i < n; i++) {
        while (s.top >= 1 && orientation(nextToTop(&s), top(&s), points[i]) != 2) {
            pop(&s);
        }
        push(&s, points[i]);
    }

    // Step 5: Copy the stack contents to the result array for the convex hull
    *hullSize = s.top + 1;
    Coord* hull = (Coord*)malloc((*hullSize) * sizeof(Coord));
    for (i = 0; i < *hullSize; i++) {
        hull[i] = s.points[i];
    }

    // Free stack memory and return the hull
    free(s.points);
    return hull;
}
