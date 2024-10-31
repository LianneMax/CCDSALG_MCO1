// main1.c - Driver program for Graham's Scan with Selection Sort (Slow Version)
#include <stdio.h>
#include "stack.h"
#include "sort.h"

#define MAX_POINTS 32768 // Define a maximum limit for points to avoid dynamic allocation

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
    if (n > MAX_POINTS) {
        printf("Error: Number of points exceeds the maximum limit of %d.\n", MAX_POINTS);
        fclose(input);
        return 1;
    }

    // Define statically allocated arrays for points and hull
    Coord points[MAX_POINTS];
    Coord hull[MAX_POINTS];

    // Read the x and y coordinates for each point
    for (i = 0; i < n; i++) {
        fscanf(input, "%lf %lf", &points[i].x, &points[i].y);
    }
    fclose(input); // Close the input file after reading all points

    // Calculate the convex hull using grahamScan1 (with selection sort) and store the result in hull
    int hullSize; // Variable to store the number of points in the hull
    Coord* hullResult = grahamScan1(points, n, &hullSize);

    if (hullResult == NULL) {
        printf("Error: Convex hull calculation failed.\n");
        return 1;
    }

    // Copy hull result to the statically allocated hull array
    for (i = 0; i < hullSize; i++) {
        hull[i] = hullResult[i];
    }

    // Open the output file for writing
    FILE* output = fopen(outputFile, "w");
    if (!output) {
        printf("Error opening output file: %s\n", outputFile);
        return 1;
    }

    // Write the number of points in the convex hull to the first line of the output file
    fprintf(output, "%d\n", hullSize);

    // Write each point in the convex hull to the output file with aligned decimals
    for (i = 0; i < hullSize; i++) {
        fprintf(output, "%10.6lf  %10.6lf\n", hull[i].x, hull[i].y); // Fixed width for alignment
    }

    // Close the output file after writing all points
    fclose(output);

    // Inform the user that the convex hull has been written to the specified output file
    printf("Convex hull written to %s\n", outputFile);
    return 0;
}

