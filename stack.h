#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>

// Define a structure for coordinates (points)
typedef struct {
    double x, y;
} Coord;

// Define a structure for the stack
typedef struct {
    Coord* points;  // Array to store points
    int top;        // Index of the top element
    int maxSize;    // Maximum stack size (up to 32,768)
} Stack;

// Stack operation declarations
void createStack(Stack* s, int size);
void push(Stack* s, Coord p);
Coord pop(Stack* s);
Coord top(Stack* s);
Coord nextToTop(Stack* s);
int isEmpty(Stack* s);
int isFull(Stack* s);

#endif

