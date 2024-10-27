#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

// Function to initialize the stack with a given size
// Ensures the stack size does not exceed the maximum of 32,768 elements
void createStack(Stack* s, int size) {
    if (size > 32768) {
        printf("Error: Stack size exceeds the maximum allowed limit of 32768.\n");
        exit(1);
    }
    s->points = (Coord*)malloc(size * sizeof(Coord)); // Allocate memory for stack points
    s->top = -1; // Initialize the top index to -1 (empty stack)
    s->maxSize = size; // Set the maximum stack size
}

// Function to push a point onto the stack
// Adds an element to the top of the stack if it's not full
void push(Stack* s, Coord p) {
    if (isFull(s) == 0) {
        s->top = s->top + 1; // Increment the top index
        s->points[s->top] = p; // Assign the point to the new top position
    } else {
        printf("Stack overflow: Cannot push more elements.\n");
    }
}

// Function to pop a point from the stack
// Removes and returns the top element from the stack if it's not empty
Coord pop(Stack* s) {
    if (isEmpty(s) == 0) {
        Coord popped = s->points[s->top]; // Store the top point
        s->top = s->top - 1; // Decrement the top index
        return popped; // Return the popped point
    } else {
        printf("Stack underflow: Cannot pop elements from an empty stack.\n");
        exit(1);
    }
}

// Function to return the top element of the stack without removing it
Coord top(Stack* s) {
    if (isEmpty(s) == 0) {
        return s->points[s->top]; // Return the top point without modifying the stack
    } else {
        printf("Stack is empty: No top element available.\n");
        exit(1);
    }
}

// Function to return the element below the top element
// Useful for Graham's Scan when evaluating the second-to-last point
Coord nextToTop(Stack* s) {
    if (s->top >= 1) { // Check that the stack has at least two elements
        return s->points[s->top - 1]; // Return the next-to-top element
    } else {
        printf("Insufficient elements in stack: Cannot retrieve next-to-top element.\n");
        exit(1);
    }
}

// Function to check if the stack is empty
// Returns 1 if empty, 0 otherwise
int isEmpty(Stack* s) {
    if (s->top == -1) {
        return 1;
    } else {
        return 0;
    }
}

// Function to check if the stack is full
// Returns 1 if full, 0 otherwise
int isFull(Stack* s) {
    if (s->top == s->maxSize - 1) {
        return 1;
    } else {
        return 0;
    }
}

