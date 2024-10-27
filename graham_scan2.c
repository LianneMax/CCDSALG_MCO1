#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"
#include "sort.h"

// Orientation function to determine orientation of three points
int orientation(Coord p, Coord q, Coord r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    return (val == 0) ? 0 : (val > 0) ? 1 : 2;
}

// Graham's Scan function using Heap Sort for the fast version
Coord* grahamScan2(Coord points[], int n, int* hullSize) {
    int i, x; // Declare loop variables here

    if (n < 3) {
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

    // Step 2: Place the anchor point at the beginning (swap with the first element)
    Coord temp = points[0];
    points[0] = points[minY];
    points[minY] = temp;
    Coord p0 = points[0];

    // Step 3: Sort the points by polar angle with respect to the anchor using heap sort
    heapSort(points + 1, n - 1, p0);

    // End timing for heap sort and print elapsed time
    double timeElapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("Heap Sort took: %.6lf seconds\n", timeElapsed);

    // Step 4: Initialize the stack and push the first three points
    Stack s;
    createStack(&s, n);
    push(&s, points[0]);
    push(&s, points[1]);
    push(&s, points[2]);

    // Step 5: Process the remaining points
    for (x = 3; x < n; x++) {
        while (s.top >= 1 && orientation(nextToTop(&s), top(&s), points[x]) != 2) {
            pop(&s);
        }
        push(&s, points[x]);
    }

    // Step 6: Copy stack contents to an array for the result
    *hullSize = s.top + 1;
    Coord* hull = (Coord*)malloc((*hullSize) * sizeof(Coord));
    for (i = 0; i < *hullSize; i++) {
        hull[i] = s.points[i];
    }

    // Free stack memory
    free(s.points);

    return hull;
}




