// graham_scan2.c - Graham's Scan with Heap Sort (Fast Version)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"
#include "sort.h"

// Function to determine the orientation of three points
// Returns 0 if points are collinear, 1 if clockwise, 2 if counterclockwise
int orientation(Coord p, Coord q, Coord r) {
    // Calculate the cross product to determine orientation
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    // Return 0 if collinear, 1 if clockwise, or 2 if counterclockwise
    if (val == 0) {
        return 0;  // Collinear
    } else if (val > 0) {
        return 1;  // Clockwise
    } else {
        return 2;  // Counterclockwise
    }
}

// Graham's Scan using Heap Sort
Coord* grahamScan2(Coord points[], int n, int* hullSize) {
    int i, x;

    // Check if there are enough points to form a convex hull
    if (n < 3) {
        printf("Convex hull is not possible with less than 3 points.\n");
        *hullSize = 0;
        return NULL;
    }

    // Start timing for heap sort
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

    // Step 2: Sort points by polar angle using heap sort
    heapSort(points + 1, n - 1, p0);

    // End timing and print elapsed time
    double timeElapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("Heap Sort took: %.6lf seconds\n", timeElapsed);

    // Step 3: Initialize the stack and add the first three points
    Stack s;
    createStack(&s, n);
    push(&s, points[0]);
    push(&s, points[1]);
    push(&s, points[2]);

    // Step 4: Process remaining points to construct the convex hull
    for (x = 3; x < n; x++) {
        while (s.top >= 1 && orientation(nextToTop(&s), top(&s), points[x]) != 2) {
            pop(&s);
        }
        push(&s, points[x]);
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





