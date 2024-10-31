// main2.c - Driver program for Graham's Scan with Heap Sort (Fast Version)
#include <stdio.h>
#include "stack.h"
#include "sort.h"

#define MaxPoints 32768  // Define a maximum number of points

// Declare grahamScan2 so that main2.c can call it
// grahamScan2 calculates the convex hull using heap sort
void grahamScan2(Coord points[], int n, int* hullSize, Coord hull[]);

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

    // Read the x and y coordinates for each point
    for (i = 0; i < n; i++) {
        if (fscanf(input, "%lf %lf", &points[i].x, &points[i].y) != 2) {
            printf("Error reading coordinates for point %d.\n", i);
            fclose(input); // Close input file before exiting due to read error
            return 1;
        }
    }
    fclose(input); // Close the input file after reading all points

    // Define static array for hull with maximum size as MaxPoints
    Coord hull[MaxPoints];
    int hullSize; // Variable to store the number of points in the hull

    // Calculate the convex hull using grahamScan2 (with heap sort)
    grahamScan2(points, n, &hullSize, hull);

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
        fprintf(output,"%10.6lf  %10.6lf\n", hull[i].x, hull[i].y); // Fixed width for alignment
    }

    // Close the output file after writing all points
    fclose(output);

    // Inform the user that the convex hull has been written to the specified output file
    printf("Convex hull written to %s\n", outputFile);
    return 0;
}

