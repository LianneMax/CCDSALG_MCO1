#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

// Initialize the stack with a given size
void createStack(Stack* s, int size) {
    if (size > 32768) {
        printf("Error: Stack size exceeds the maximum allowed limit of 32768.\n");
        exit(1);
    }
    s->points = (Coord*)malloc(size * sizeof(Coord));
    s->top = -1;
    s->maxSize = size;
}

// Push an element onto the stack
void push(Stack* s, Coord p) {
    if (!isFull(s)) {
        s->points[++(s->top)] = p;
    } else {
        printf("Stack overflow: Cannot push more elements.\n");
    }
}

// Pop an element from the stack
Coord pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->points[(s->top)--];
    } else {
        printf("Stack underflow: Cannot pop elements from an empty stack.\n");
        exit(1);
    }
}

// Return the top element of the stack without removing it
Coord top(Stack* s) {
    if (!isEmpty(s)) {
        return s->points[s->top];
    } else {
        printf("Stack is empty: No top element available.\n");
        exit(1);
    }
}

// Return the element below the top element
Coord nextToTop(Stack* s) {
    if (s->top >= 1) {
        return s->points[s->top - 1];
    } else {
        printf("Insufficient elements in stack: Cannot retrieve next-to-top element.\n");
        exit(1);
    }
}

// Check if the stack is empty
int isEmpty(Stack* s) {
    return s->top == -1;
}

// Check if the stack is full
int isFull(Stack* s) {
    return s->top == s->maxSize - 1;
}

