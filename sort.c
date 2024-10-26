#include <stdio.h>
#include "sort.h"
#define MAX 32768

double polarAngle(Coord p1, Coord p2, Coord anchor)
{
  	double polarAngleValue = (p1.x - anchor.x) * (p2.y - anchor.y) - (p1.y - anchor.y) * (p2.x - anchor.x);
	double q1 = (p1.x - anchor.x) * (p1.x - anchor.x) + (p1.y - anchor.y) * (p1.y - anchor.y);
        double q2 = (p2.x - anchor.x) * (p2.x - anchor.x) + (p2.y - anchor.y) * (p2.y - anchor.y);
	
	if (polarAngleValue > 0) 
	{
		return 1;
	}
	else if (polarAngleValue < 0)
	{
		return -1;
	}
	else if (q1 < q2) //polarAngleValue = 0
	{
		return 1; 
	}
        else if (q1 > q2)
	{
		return -1;  
	}	
	else if (p1.x < p2.x)
	{
		return 1;
	}
	else if (p1.x > p2.x)
	{
		return -1;
	}
	else
	{
		return 0;
	}
} //pls fix the syntax errors

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
} // done 

//fast sort (heap sort)
void swap(Coord* a, Coord* b) {
    Coord temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Coord points[], int n, int i, Coord p0) {
    int largest = i;        // Initialize largest as root
    int left = 2 * i + 1;   // Left child
    int right = 2 * i + 2;  // Right child

    // Compare left child with the root based on polar angle
    if (left < n && polarAngle(p0, points[left], p0) > polarAngle(p0, points[largest], p0)) {
        largest = left;
    }

    // Compare right child with the largest element
    if (right < n && polarAngle(p0, points[right], p0) > polarAngle(p0, points[largest], p0)) {
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
