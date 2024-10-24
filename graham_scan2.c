//This for the fast version

// graham_scan2.c
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "sort.h"
#include <time.h>

int orientation(Point p, Point q, Point r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

void grahamScan2(Point points[], int n) {
    int minY = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].y < points[minY].y || (points[i].y == points[minY].y && points[i].x < points[minY].x)) {
            minY = i;
        }
    }
    Point temp = points[0];
    points[0] = points[minY];
    points[minY] = temp;

    Point p0 = points[0];
    heapSort(points + 1, n - 1, p0);

    Stack s;
    createStack(&s, n);
    push(&s, points[0]);
    push(&s, points[1]);
    push(&s, points[2]);

    for (int i = 3; i < n; i++) {
        while (orientation(nextToTop(&s), top(&s), points[i]) != 2)
            pop(&s);
        push(&s, points[i]);
    }

    FILE *outputFile = fopen("output2.txt", "w");
    int m = s.top + 1;
    fprintf(outputFile, "%d\n", m);
    for (int i = 0; i < m; i++) {
        fprintf(outputFile, "%.6lf %.6lf\n", s.points[i].x, s.points[i].y);
    }
    fclose(outputFile);
}