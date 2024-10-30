// graham_scan1.c - Graham's Scan with Selection Sort (Slow Version)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"
#include "sort.h"

#define STEP  (1024)  // Increment for number of points
#define LIMIT (32768) // Maximum number of points

// Function to determine the orientation of three points
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

// Graham's Scan with Selection Sort and empirical timing
Coord* grahamScan1(Coord points[], int n, int* hullSize) {
    int i;

    // Check if there are enough points to form a convex hull
    if (n < 3) {
        printf("Convex hull is not possible with less than 3 points.\n");
        *hullSize = 0;
        return NULL;
    }

    // Start timing for selection sort and Graham’s scan
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

    // End timing and calculate elapsed time
    clock_t end = clock();
    double timeElapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Number of points: %6d, Execution time: %.6lf seconds\n", n, timeElapsed);

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

    free(s.points);
    return hull;
}