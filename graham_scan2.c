#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"
#include "sort.h"

// Helper function to determine the orientation of three points
int orientation(Coord p, Coord q, Coord r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;               // Collinear points
    return (val > 0) ? 1 : 2;             // Clockwise (1) or Counterclockwise (2)
}

// Graham's Scan function using Heap Sort for the fast version
Coord* grahamScan2(Coord points[], int n, int* hullSize) {
    if (n < 3) {
        printf("Convex hull is not possible with less than 3 points.\n");
        *hullSize = 0;
        return NULL;
    }

    // Start the timer
    clock_t start = clock();

    // Find the point with the lowest y-coordinate (or lowest x-coordinate if tied)
    int minY = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].y < points[minY].y || (points[i].y == points[minY].y && points[i].x < points[minY].x)) {
            minY = i;
        }
    }

    // Place the anchor point at the beginning
    Coord temp = points[0];
    points[0] = points[minY];
    points[minY] = temp;
    Coord p0 = points[0];

    // Sort points by polar angle using heap sort
    heapSort(points + 1, n - 1, p0);

    // Initialize the stack and add the first three points
    Stack s;
    createStack(&s, n);
    push(&s, points[0]);
    push(&s, points[1]);
    push(&s, points[2]);

    // Process remaining points
    for (int i = 3; i < n; i++) {
        while (orientation(nextToTop(&s), top(&s), points[i]) != 2) {
            pop(&s);
        }
        push(&s, points[i]);
    }

    // Copy stack contents to an array for the result
    *hullSize = s.top + 1;
    Coord* hull = (Coord*)malloc((*hullSize) * sizeof(Coord));
    for (int i = 0; i < *hullSize; i++) {
        hull[i] = s.points[i];
    }

    // End timer
    clock_t end = clock();
    double timeElapsed = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    printf("Time elapsed (Heap Sort): %.3lf ms\n", timeElapsed);

    // Free the stack memory
    free(s.points);

    return hull;
}
