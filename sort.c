#include <stdio.h>
#include "sort.h"
#define MAX 32768

double polarAngle(Coord p1, Coord p2, Coord anchor)
{
  // statement (idk the formula for polar angle )
	// return value 
} // not yet done

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
