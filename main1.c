// main1.c - Driver program for Graham's Scan with Selection Sort (Slow Version)
#include <stdio.h>
#include "stack.h"
#include "sort.h"

#define MaxPoints 32768  // Define a maximum number of points

// Declare grahamScan1 so that main1.c can call it
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
    if (fscanf(input, "%d", &n) != 1 || n > MaxPoints) {
        printf("Error: Invalid number of points or exceeds maximum allowed (%d).\n", MaxPoints);
        fclose(input); // Close input file before exiting due to read error
        return 1;
    }
    
    // Define static array for storing the points
    Coord points[MaxPoints];

    int actualCount = 0; // Track actual number of coordinates read

    // Read the x and y coordinates for each point and count them
    while (fscanf(input, "%lf %lf", &points[actualCount].x, &points[actualCount].y) == 2) {
        actualCount++;
        if (actualCount > MaxPoints) {
            printf("Error: Number of points exceeds maximum allowed (%d).\n", MaxPoints);
            fclose(input);
            return 1;
        }
    }
    fclose(input); // Close input file after reading all points

    // Check if the actual count matches the initial value of n
    if (actualCount != n) {
        printf("Error: The specified number of points (%d) does not match the actual count of coordinates read (%d).\n", n, actualCount);
        return 1;
    }

    // Calculate the convex hull using grahamScan1 (with selection sort) and store the result in hull
    int hullSize; // Variable to store the number of points in the hull
    Coord* hullResult = grahamScan1(points, n, &hullSize);

    if (hullResult == NULL) {
        printf("Error: Convex hull calculation failed.\n");
        return 1;
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
        fprintf(output, "%10.6lf  %10.6lf\n", hullResult[i].x, hullResult[i].y);
    }

    // Close the output file after writing all points
    fclose(output);

    // Inform the user that the convex hull has been written to the specified output file
    printf("Convex hull written to %s\n", outputFile);
    return 0;
}
