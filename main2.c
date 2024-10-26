#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "graham_scan2.c"

int main() {
    char inputFile[100], outputFile[100];
    printf("Enter input file name (with extension): ");
    scanf("%s", inputFile);
    printf("Enter output file name (with extension): ");
    scanf("%s", outputFile);

    // Open the input file
    FILE* input = fopen(inputFile, "r");
    if (!input) {
        printf("Error opening input file!\n");
        return 1;
    }

    // Read the number of points
    int n;
    fscanf(input, "%d", &n);

    // Allocate memory for points
    Coord* points = (Coord*)malloc(n * sizeof(Coord));
    if (points == NULL) {
        printf("Memory allocation failed.\n");
        fclose(input);
        return 1;
    }

    // Read the points from the file
    for (int i = 0; i < n; i++) {
        fscanf(input, "%lf %lf", &points[i].x, &points[i].y);
    }
    fclose(input); // Close the input file

    // Call the fast version of Graham's Scan (heap sort)
    int hullSize;
    Coord* hull = grahamScan2(points, n, &hullSize);

    // Open the output file
    FILE* output = fopen(outputFile, "w");
    if (!output) {
        printf("Error opening output file!\n");
        free(points);
        free(hull);
        return 1;
    }

    // Write the convex hull points to the output file
    fprintf(output, "%d\n", hullSize);  // Number of points in the convex hull
    for (int i = 0; i < hullSize; i++) {
        fprintf(output, "%.6lf %.6lf\n", hull[i].x, hull[i].y);
    }

    // Close the output file and free allocated memory
    fclose(output);
    free(points);
    free(hull);

    printf("Convex hull written to %s\n", outputFile);
    return 0;
}
