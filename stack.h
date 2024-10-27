#ifndef STACK_H
#define STACK_H

#include <stdlib.h> // Standard library for memory allocation

// Structure to represent a coordinate (point) in 2D space
typedef struct {
    double x; // X-coordinate of the point
    double y; // Y-coordinate of the point
} Coord;

// Structure to represent a stack of coordinates
typedef struct {
    Coord* points;  // Dynamic array to store points in the stack
    int top;        // Index of the top element in the stack
    int maxSize;    // Maximum number of elements the stack can hold (up to 32,768)
} Stack;

// Stack operation function declarations

// Function to initialize the stack with a given maximum size
// Parameters: pointer to Stack structure, maximum size of the stack
void createStack(Stack* s, int size);

// Function to add a point to the top of the stack
// Parameters: pointer to Stack structure, point (Coord) to add
void push(Stack* s, Coord p);

// Function to remove and return the top point from the stack
// Parameters: pointer to Stack structure
// Returns: top point (Coord) from the stack
Coord pop(Stack* s);

// Function to retrieve the top point from the stack without removing it
// Parameters: pointer to Stack structure
// Returns: top point (Coord) from the stack
Coord top(Stack* s);

// Function to retrieve the point below the top point without removing it
// Parameters: pointer to Stack structure
// Returns: next-to-top point (Coord) from the stack
Coord nextToTop(Stack* s);

// Function to check if the stack is empty
// Parameters: pointer to Stack structure
// Returns: 1 if stack is empty, 0 otherwise
int isEmpty(Stack* s);

// Function to check if the stack is full
// Parameters: pointer to Stack structure
// Returns: 1 if stack is full, 0 otherwise
int isFull(Stack* s);

#endif // End of STACK_H


