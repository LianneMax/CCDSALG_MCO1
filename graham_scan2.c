// graham_scan2.c - Graham's Scan with Heap Sort (Fast Version) using fixed-size stack
#include <stdio.h>
#include <time.h>
#include "stack.h"
#include "sort.h"

// Function to determine the orientation of three points
int orientation(Coord p, Coord q, Coord r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;        // Collinear
    else if (val > 0) return 1;    // Clockwise
    else return 2;                 // Counterclockwise
}

// Graham's Scan with Heap Sort
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

    // Move the anchor point to the first position
    Coord temp = points[0];
    points[0] = points[minY];
    points[minY] = temp;
    Coord p0 = points[0];

    // Sort points by polar angle using selection sort
    heapSort(points + 1, n - 1, p0);

    // Initialize the stack and add the first three points
    Stack s;
    Create(&s);                  // Initialize the stack
    Push(&s, points[0]);         // Push the first three points
    Push(&s, points[1]);
    Push(&s, points[2]);

    // Process remaining points
    for (x = 3; x < n; x++) {
        while (s.top >= 1 && orientation(*NextToTop(&s), *Top(&s), points[x]) != 2) {
            Pop(&s);             // Remove the top point if it makes a non-left turn
        }
        Push(&s, points[x]);     // Push the current point onto the stack
    }

    // Copy the stack contents to the result array for the convex hull
    *hullSize = s.top + 1;
    static Coord hull[MaxStack]; // Fixed-size array for hull storage
    for (i = 0; i < *hullSize; i++) {
        hull[i] = s.points[i];
    }

    // End timing and calculate elapsed time
    clock_t end = clock();

    printf("Number of points: %6d \nExecution time: %.6lf milliseconds\n", n, (double)(end - start) * 1000.0 / CLOCKS_PER_SEC);

    return hull;
}
