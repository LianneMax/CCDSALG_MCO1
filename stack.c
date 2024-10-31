#include <stdio.h>
#include "stack.h"

// Function to initialize the stack
// Ensures the stack size does not exceed the maximum allowed limit
int Create(Stack* s) {
    s->top = -1; // Initialize the top index to -1 (empty stack)
    return 0;    // Success
}

// Function to push an element onto the stack
// Adds an element to the top of the stack if it's not full
int Push(Stack* s, Coord elem) {
    if (IsFull(s) == 0) {
        s->top = s->top + 1;        // Increment the top index
        s->points[s->top] = elem;   // Assign the element to the new top position
        return 0;                   // Success
    } else {
        printf("Stack overflow: Cannot push more elements.\n");
        return -1;                  // Error
    }
}

// Function to pop an element from the stack
// Removes and returns the top element from the stack if it's not empty
Coord* Pop(Stack* s) {
    if (IsEmpty(s) == 0) {
        Coord* popped = &(s->points[s->top]); // Pointer to the top element
        s->top = s->top - 1;                  // Decrement the top index
        return popped;                        // Return pointer to the popped element
    } else {
        printf("Stack underflow: Cannot pop elements from an empty stack.\n");
        return NULL;                          // Error: stack empty
    }
}

// Function to return the top element of the stack without removing it
Coord* Top(Stack* s) {
    if (IsEmpty(s) == 0) {
        return &(s->points[s->top]); // Pointer to the top element
    } else {
        printf("Stack is empty: No top element available.\n");
        return NULL;                 // Error: stack empty
    }
}

// Function to return the element below the top element (Next-to-top)
// Useful for Graham's Scan when evaluating the second-to-last point
Coord* NextToTop(Stack* s) {
    if (s->top >= 1) { // Check that the stack has at least two elements
        return &(s->points[s->top - 1]); // Pointer to the next-to-top element
    } else {
        printf("Insufficient elements in stack: Cannot retrieve next-to-top element.\n");
        return NULL;                     // Error: not enough elements
    }
}

// Function to check if the stack is empty
// Returns 1 if empty, 0 otherwise
int IsEmpty(Stack* s) {
    if (s->top == -1) {
        return 1; // Stack is empty
    }
    return 0; // Stack is not empty
}

// Function to check if the stack is full
// Returns 1 if full, 0 otherwise
int IsFull(Stack* s) {
    if (s->top == MaxStack - 1) {
        return 1; // Stack is full
    }
    return 0; // Stack is not full
}