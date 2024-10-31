#ifndef STACK_H
#define STACK_H

// Define the maximum stack size
#define MaxStack 32768


// Structure to represent a coordinate (point) in 2D space
typedef struct {
    double x; // X-coordinate of the point
    double y; // Y-coordinate of the point
} Coord;

// Define a structure for the stack
typedef struct {
    Coord points[MaxStack]; // Fixed-size array for stack points
    int top;                // Index of the top element
} Stack;

// Stack operation function declarations

// Function to initialize the stack with a given maximum size
// Parameters: pointer to Stack structure, maximum size of the stack
int Create(Stack* s);

// Function to add a point to the top of the stack
// Parameters: pointer to Stack structure, point (Coord) to add
int Push(Stack* s, Coord elem);

// Function to remove and return the top point from the stack
// Parameters: pointer to Stack structure
// Returns: top point (Coord) from the stack
Coord* Pop(Stack* s);

// Function to retrieve the top point from the stack without removing it
// Parameters: pointer to Stack structure
// Returns: top point (Coord) from the stack
Coord* Top(Stack* s);

// Function to retrieve the point below the top point without removing it
// Parameters: pointer to Stack structure
// Returns: next-to-top point (Coord) from the stack
Coord* NextToTop(Stack* s);

// Function to check if the stack is empty
// Parameters: pointer to Stack structure
// Returns: 1 if stack is empty, 0 otherwise
int IsEmpty(Stack* s);

// Function to check if the stack is full
// Parameters: pointer to Stack structure
// Returns: 1 if stack is full, 0 otherwise
int IsFull(Stack* s);

#endif


