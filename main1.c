#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "sort.h"

// Declare grahamScan1 so that main1.c can call it
Coord* grahamScan1(Coord points[], int n, int* hullSize);

int main(int argc, char *argv[]) {
    int i;

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

    for (i = 0; i < n; i++) {
        fscanf(input, "%lf %lf", &points[i].x, &points[i].y);
    }
    fclose(input);

    int hullSize;
    Coord* hull = grahamScan1(points, n, &hullSize);  // grahamScan1 will be linked during compilation

    FILE* output = fopen(outputFile, "w");
    if (!output) {
        printf("Error opening output file: %s\n", outputFile);
        free(points);
        free(hull);
        return 1;
    }

    fprintf(output, "%d\n", hullSize);
    for (i = 0; i < hullSize; i++) {
        fprintf(output, "%.6lf %.6lf \n", hull[i].x, hull[i].y);
    }

    fclose(output);
    free(points);
    free(hull);

    printf("Convex hull written to %s\n", outputFile);
    return 0;
}
