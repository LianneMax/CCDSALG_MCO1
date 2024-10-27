#include "sort.h"
#include <stdio.h> // For standard I/O functions

// Swap function used by heap sort
void swap(Coord* a, Coord* b) {
    Coord temp = *a;
    *a = *b;
    *b = temp;
}

int compareByPolarAngle(const Coord* p1, const Coord* p2, Coord anchor) {
    double cross_product = (p1->x - anchor.x) * (p2->y - anchor.y) - (p1->y - anchor.y) * (p2->x - anchor.x);
    if (cross_product > 0) return -1;    // p1 is counterclockwise to p2
    if (cross_product < 0) return 1;     // p2 is counterclockwise to p1
    // If collinear, sort by distance to the anchor
    double dist1 = (p1->x - anchor.x) * (p1->x - anchor.x) + (p1->y - anchor.y) * (p1->y - anchor.y);
    double dist2 = (p2->x - anchor.x) * (p2->x - anchor.x) + (p2->y - anchor.y) * (p2->y - anchor.y);
    return dist1 < dist2 ? -1 : 1;
}

// Heapify function for double array
void heapifyDouble(double arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }

    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }

    if (largest != i) {
        double temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapifyDouble(arr, n, largest);
    }
}

// Heap Sort for double array
void heapSortDouble(double arr[], int n) {
    int i;
    for (i = n / 2 - 1; i >= 0; i--) {
        heapifyDouble(arr, n, i);
    }

    for (i = n - 1; i > 0; i--) {
        double temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapifyDouble(arr, i, 0);
    }
}

// Heapify function for Coord array using cross product comparison
void heapifyCoord(Coord points[], int n, int i, Coord anchor) {
    int largest = i, left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && compareByPolarAngle(&points[left], &points[largest], anchor) < 0) {
        largest = left;
    }

    if (right < n && compareByPolarAngle(&points[right], &points[largest], anchor) < 0) {
        largest = right;
    }

    if (largest != i) {
        swap(&points[i], &points[largest]);
        heapifyCoord(points, n, largest, anchor);
    }
}

// Heap Sort for Coord array by polar angle
void heapSortCoord(Coord points[], int n, Coord anchor) {
    int i;

    for (i = n / 2 - 1; i >= 0; i--) {
        heapifyCoord(points, n, i, anchor);
    }

    for (i = n - 1; i > 0; i--) {
        swap(&points[0], &points[i]);
        heapifyCoord(points, i, 0, anchor);
    }
}

// Main function to test both heap sort functions
int main() {
    // Test for double array
    double arr[] = {12.5, 11.3, 13.7, 5.2, 6.8, 7.1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i;

    printf("Original double array:\n");
    for (i = 0; i < n; i++) {
        printf("%.2f ", arr[i]);
    }
    printf("\n");

    heapSortDouble(arr, n);

    printf("Sorted double array:\n");
    for (i = 0; i < n; i++) {
        printf("%.2f ", arr[i]);
    }
    printf("\n");

    // Test for Coord array
    Coord points[] = {
        {5.0, 5.0}, {10.0, 2.5}, {5.0, 10.0}, {10.0, 0.0}, {7.5, 0.0}, {5.0, 0.0}, {0.0, 0.0}, {1.0, 8.0}, {0.0, 10.0}
    };
    int m = sizeof(points) / sizeof(points[0]);
    Coord anchor = {0, 0}; // Sorting with respect to origin

    printf("\nOriginal Coord array:\n");
    for (i = 0; i < m; i++) {
        printf("(%6.2lf, %6.2lf) | ", points[i].x, points[i].y);
    }
    printf("\n");

    heapSortCoord(points, m, anchor);

    printf("Sorted Coord array by polar angle:\n");
    for (i = 0; i < m; i++) {
        printf("(%6.2lf, %6.2lf) | ", points[i].x, points[i].y);
    }
    printf("\n");

    return 0;
}