#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"
#include "sort.h"

int orientation(Coord p, Coord q, Coord r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    return (val == 0) ? 0 : (val > 0) ? 1 : 2;
}

Coord* grahamScan2(Coord points[], int n, int* hullSize) {
    int i; // Declare loop variable here to avoid re-declaration errors

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
    for (i = 3; i < n; i++) {
        while (s.top >= 1 && orientation(nextToTop(&s), top(&s), points[i]) != 2) {
            pop(&s);
        }
        push(&s, points[i]);
    }

    // Step 6: Copy stack contents to an array for the result
    *hullSize = s.top + 1;
    Coord* hull = (Coord*)malloc((*hullSize) * sizeof(Coord));
    for (i = 0; i < *hullSize; i++) {
        hull[i] = s.points[i];
    }

    // Free the stack memory
    free(s.points);

    return hull;
}



