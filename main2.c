#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// Declare grahamScan2 so that main2.c can call it
Coord* grahamScan2(Coord points[], int n, int* hullSize);

int main(int argc, char *argv[]) {
    int i;  // Declare 'i' at the beginning of the function

    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        return 1;
    }

    char *inputFile = argv[1];
    char *outputFile = argv[2];

    FILE* input = fopen(inputFile, "r");
    if (!input) {
        printf("Error opening input file: %s\n", inputFile);
        return 1;
    }

    int n;
    fscanf(input, "%d", &n);

    Coord* points = (Coord*)malloc(n * sizeof(Coord));
    if (points == NULL) {
        printf("Memory allocation failed.\n");
        fclose(input);
        return 1;
    }

    for (i = 0; i < n; i++) {  // Use the pre-declared 'i'
        fscanf(input, "%lf %lf", &points[i].x, &points[i].y);
    }
    fclose(input);

    int hullSize;
    Coord* hull = grahamScan2(points, n, &hullSize);

    FILE* output = fopen(outputFile, "w");
    if (!output) {
        printf("Error opening output file: %s\n", outputFile);
        free(points);
        free(hull);
        return 1;
    }

    fprintf(output, "%d\n", hullSize);
    for (i = 0; i < hullSize; i++) {  // Reuse 'i'
        fprintf(output, "%.6lf %.6lf\n", hull[i].x, hull[i].y);
    }

    fclose(output);
    free(points);
    free(hull);

    printf("Convex hull written to %s\n", outputFile);
    return 0;
}
