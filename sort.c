#include <stdio.h>
#include "sort.h"
#define MAX 32768

double polarAngle(Coord p1, Coord p2, Coord anchor)
{
  // statement (idk the formula for polar angle )
	// return value 
} // not yet done

//slow sort
void selectSort(int n, Coord points[], Coord anchor)
{
	int i, j, low;
	Coord temp;
	
	for (i = 0; i < n-1; i++){
		low = i;
		for (j = i+1; j < n; j++){
			if (polarAngle > 0)
			low = j;
			}
	}	

  // select sort algo  
	temp = points[i];
	points[i] = points[low];
	points[low] = temp;	
} // not yet done 

//fast sort
//heap sort
void swap(Coord* a, Coord* b) {
    Coord temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Coord points[], int n, int i, Coord p0) {
    int largest = i;  // Initialize largest as root
    int left = 2 * i + 1;  // left child
    int right = 2 * i + 2; // right child

    // Compare left child with the root based on polar angle
    if (left < n && polarAngle(p0, points[left]) > polarAngle(p0, points[largest])) {
        largest = left;
    }

    // Compare right child with the largest element
    if (right < n && polarAngle(p0, points[right]) > polarAngle(p0, points[largest])) {
        largest = right;
    }

    // If the largest is not the root, swap and continue heapifying
    if (largest != i) {
        swap(&points[i], &points[largest]);
        heapify(points, n, largest, p0);
    }
}

void heapSort(Coord points[], int n, Coord p0) {
    // Build the heap (rearrange the array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(points, n, i, p0);
    }

    // Extract elements from the heap one by one
    for (int i = n - 1; i >= 0; i--) {
        // Move current root to end
        swap(&points[0], &points[i]);

        // Call heapify on the reduced heap
        heapify(points, i, 0, p0);
    }
}