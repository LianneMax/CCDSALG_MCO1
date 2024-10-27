// main1.c - Driver program for Graham's Scan with Selection Sort (Slow Version)
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "sort.h"

// Declare grahamScan1 function so it can be used in main1.c
// grahamScan1 calculates the convex hull using selection sort
Coord* grahamScan1(Coord points[], int n, int* hullSize);

int main(int argc, char *argv[]) {
    int i; // Loop variable for iterating over points

    // Ensure that the program is run with exactly two arguments (input and output file names)
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        return 1;
    }

    // Assign input and output file names from command line arguments
    char *inputFile = argv[1];
    char *outputFile = argv[2];

    // Open the input file for reading
    FILE* input = fopen(inputFile, "r");
    if (!input) {
        printf("Error opening input file: %s\n", inputFile);
        return 1;
    }

    // Read the number of points from the first line of the input file
    int n;
    fscanf(input, "%d", &n);

    // Allocate memory to store the points
    Coord* points = (Coord*)malloc(n * sizeof(Coord));
    if (points == NULL) {
        printf("Memory allocation failed.\n");
        fclose(input); // Close input file before exiting due to memory allocation error
        return 1;
    }

    // Read the x and y coordinates for each point
    for (i = 0; i < n; i++) {
        fscanf(input, "%lf %lf", &points[i].x, &points[i].y);
    }
    fclose(input); // Close the input file after reading all points

    // Calculate the convex hull using grahamScan1 (with selection sort) and store the result in hull
    int hullSize; // Variable to store the number of points in the hull
    Coord* hull = grahamScan1(points, n, &hullSize);

    // Open the output file for writing
    FILE* output = fopen(outputFile, "w");
    if (!output) {
        printf("Error opening output file: %s\n", outputFile);
        free(points); // Free dynamically allocated memory for points
        free(hull);   // Free dynamically allocated memory for hull
        return 1;
    }

    // Write the number of points in the convex hull to the first line of the output file
    fprintf(output, "%d\n", hullSize);

    // Write each point in the convex hull to the output file, with 6 decimal places
    for (i = 0; i < hullSize; i++) {
        fprintf(output, "%.6lf %.6lf\n", hull[i].x, hull[i].y);
    }

    // Close the output file after writing all points
    fclose(output);

    // Free dynamically allocated memory for points and hull arrays
    free(points);
    free(hull);

    // Inform the user that the convex hull has been written to the specified output file
    printf("Convex hull written to %s\n", outputFile);
    return 0;
}
