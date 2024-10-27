//graham_scan1.c = slow sort [selection sort]
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"
#include "sort.h"

int orientation(Coord p, Coord q, Coord r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0; // Collinear points
    return (val > 0) ? 1 : 2; // Clockwise (1) or Counterclockwise (2)
}

Coord* grahamScan1(Coord points[], int n, int* hullSize) {
    int i;

    if (n < 3) {
        printf("Convex hull is not possible with less than 3 points.\n");
        *hullSize = 0;
        return NULL;
    }

    // Start timing for selection sort
    clock_t start = clock();

    // Find the point with the lowest y-coordinate
    int minY = 0;
    for (i = 1; i < n; i++) {
        if (points[i].y < points[minY].y || (points[i].y == points[minY].y && points[i].x < points[minY].x)) {
            minY = i;
        }
    }

    // Place the anchor point at the beginning
    Coord temp = points[0];
    points[0] = points[minY];
    points[minY] = temp;
    Coord p0 = points[0];

    // Sort points by polar angle using selection sort
    selectSort(n, points, p0);

    // End timing for selection sort and print the elapsed time
    double timeElapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("Selection Sort took: %.6lf seconds\n", timeElapsed);

    // Initialize the stack and add the first three points
    Stack s;
    createStack(&s, n);
    push(&s, points[0]);
    push(&s, points[1]);
    push(&s, points[2]);

    // Process remaining points
    for (i = 3; i < n; i++) {
        while (s.top >= 1 && orientation(nextToTop(&s), top(&s), points[i]) != 2) {
            pop(&s);
        }
        push(&s, points[i]);
    }

    *hullSize = s.top + 1;
    Coord* hull = (Coord*)malloc((*hullSize) * sizeof(Coord));
    for (i = 0; i < *hullSize; i++) {
        hull[i] = s.points[i];
    }

    free(s.points); // Free stack memory
    return hull;
}
