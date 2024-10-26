//This for the fast version

// graham_scan2.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "stack.h"
#include "sort.h"

int orientation(Point p, Point q, Point r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    //Collinear Points
    if (val == 0) {
        return 0;
    }
    
    if (val > 0) {
        return 1; // Clockwise
    } else {
        return 2; // Counterclockwise
    }
}

void grahamScan2(Point points[], int n) {

    // **Boundary Check**: Added to ensure at least 3 points for a valid convex hull
    if (n < 3) {
        printf("Convex hull is not possible with less than 3 points.\n");
        return;
    }

    //Finds the point with the lowest y-coordinate
    int minY = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].y < points[minY].y || (points[i].y == points[minY].y && points[i].x < points[minY].x)) {
            minY = i;
        }
    }

    //Anchor Placement - swaps point to the start for consistency
    Point temp = points[0];
    points[0] = points[minY];
    points[minY] = temp;

    //Corrected Sort Call - using heapSort with the proper anchor point "p0"
    Point p0 = points[0];
    heapSort(points + 1, n - 1, p0);

    //Initialize the stack and add the first three points
    Stack s;
    createStack(&s, n);
    push(&s, points[0]);
    push(&s, points[1]);
    push(&s, points[2]);

    //Process the remaining points
    for (int i = 3; i < n; i++) {
        //Orientation Check - ensures counterclockwise angle using "orientation"
        while (orientation(nextToTop(&s), top(&s), points[i]) != 2) {
            pop(&s);
        }
        push(&s, points[i]);
    }

    //File Handling - error checking for file creation
    FILE *outputFile = fopen("output2.txt", "w");
    if (!outputFile) {
        printf("Error opening output file.\n");

        //Memory Management - ensures stack memory is freed on error
        free(s.points);
        return;
    }

    //write the convex hull points to the file
    int m = s.top + 1;

    //number of points in the convex hull
    fprintf(outputFile, "%d\n", m);
    for (int i = 0; i < m; i++) {
        //x and y coordinates with 6 decimals
        fprintf(outputFile, "%.6lf %.6lf\n", s.points[i].x, s.points[i].y);
    }
    fclose(outputFile);

    //Memory Management - free stack memory after use
    free(s.points);
}