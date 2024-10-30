// graham_scan2.c - Graham's Scan with Heap Sort (Fast Version)
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

// Graham's Scan with Heap Sort and empirical timing
Coord* grahamScan2(Coord points[], int n, int* hullSize) {
    int i, x;

    if (n < 3) {
        printf("Convex hull is not possible with less than 3 points.\n");
        *hullSize = 0;
        return NULL;
    }

    // Start timing for heap sort and Graham’s scan
    clock_t start = clock();

    // Find the anchor point with the lowest y-coordinate
    int minY = 0;
    for (i = 1; i < n; i++) {
        if (points[i].y < points[minY].y || (points[i].y == points[minY].y && points[i].x < points[minY].x)) {
            minY = i;
        }
    }
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

    // Process remaining points to construct the convex hull
    for (x = 3; x < n; x++) {
        while (s.top >= 1 && orientation(nextToTop(&s), top(&s), points[x]) != 2) {
            pop(&s);
        }
        push(&s, points[x]);
    }

    // End timing and calculate elapsed time
    clock_t end = clock();
    double timeElapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Number of points: %6d \nExecution time: %.6lf seconds\n", n, timeElapsed);

    // Copy the stack contents to the result array for the convex hull
    *hullSize = s.top + 1;
    Coord* hull = (Coord*)malloc((*hullSize) * sizeof(Coord));
    for (i = 0; i < *hullSize; i++) {
        hull[i] = s.points[i];
    }

    free(s.points);
    return hull;
}