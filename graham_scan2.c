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

//Graham's Scan function using Heap Sort for the fast version
Coord* grahamScan2(Coord points[], int n, int* hullSize) {
    int i, x;

    if (n < 3) {
        printf("Convex hull is not possible with less than 3 points.\n");
        *hullSize = 0;
        return NULL;
    }

    //Start the timer
    clock_t start = clock();

    //Find the point with the lowest y-coordinate (or lowest x-coordinate if tied)
    int minY = 0;
    for (i = 1; i < n; i++) {
        if (points[i].y < points[minY].y || (points[i].y == points[minY].y && points[i].x < points[minY].x)) {
            minY = i;
        }
    }

    //Place the anchor point at the beginning (swap with the first element)
    Coord temp = points[0];
    points[0] = points[minY];
    points[minY] = temp;
    Coord p0 = points[0]; // Anchor point for sorting

    //Sort remaining points by polar angle with respect to p0 using heap sort
    heapSort(points + 1, n - 1, p0);

    //Initialize the stack and add the first three points
    Stack s;
    createStack(&s, n);
    push(&s, points[0]);
    push(&s, points[1]);
    push(&s, points[2]);

    //Process the sorted points and construct the convex hull
    for (x = 3; x < n; x++) {
        // Remove top point while it doesn't form a counterclockwise turn
        while (s.top >= 1 && orientation(nextToTop(&s), top(&s), points[x]) != 2) {
            pop(&s);
        }
        push(&s, points[x]);
    }

    //Copy stack contents to an array for the result
    *hullSize = s.top + 1;
    Coord* hull = (Coord*)malloc((*hullSize) * sizeof(Coord));
    for (i = 0; i < *hullSize; i++) {
        hull[i] = s.points[i];
    }

    //End timer and display elapsed time
    clock_t end = clock();
    double timeElapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Heap Sort took: %.6f seconds\n", timeElapsed);

    //Free stack memory
    free(s.points);

    return hull;
}