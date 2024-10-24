//This is for the fast version

// main2.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graham_scan2.c"

int main() {
    char inputFile[100], outputFile[100];
    printf("Enter input file: ");
    scanf("%s", inputFile);
    printf("Enter output file: ");
    scanf("%s", outputFile);

    FILE* input = fopen(inputFile, "r");
    if (!input) {
        printf("Error opening file!\n");
        return 1;
    }

    int n;
    fscanf(input, "%d", &n);
    Point* points = (Point*)malloc(n * sizeof(Point));

    for (int i = 0; i < n; i++) {
        fscanf(input, "%lf %lf", &points[i].x, &points[i].y);
    }
    fclose(input);

    clock_t start = clock();
    grahamScan2(points, n);
    clock_t end = clock();
    
    double timeElapsed = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    printf("Time elapsed: %.3lf ms\n", timeElapsed);
    
    free(points);
    return 0;
}