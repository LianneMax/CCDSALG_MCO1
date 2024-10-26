#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "sort.h"
#include <time.h>

int orientation(Coord p, Coord q, Coord r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;               // Collinear points
    return (val > 0) ? 1 : 2;              // Clockwise (1) or Counterclockwise (2)
}

void grahamScan2(Coord points[], int n) {
    if (n < 3) {
        printf("Convex hull is not possible with less than 3 points.\n");
        return;
    }

    // Find the point with the lowest y-coordinate
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

    // Corrected Sort Call: Using `heapSort` with the proper anchor point `p0`
    Coord p0 = points[0];
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

    // Write the result to the output file
    FILE *outputFile = fopen("output2.txt", "w");
    if (!outputFile) {
        printf("Error opening output file.\n");
        free(s.points);
        return;
    }

    int m = s.top + 1;
    fprintf(outputFile, "%d\n", m);  // Number of points in the convex hull
    for (int i = 0; i < m; i++) {
        fprintf(outputFile, "%.6lf %.6lf\n", s.points[i].x, s.points[i].y);
    }
    fclose(outputFile);

    // Free the stack memory
    free(s.points);
}
