// stack.c
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "sort.h"

void createStack(Stack* s, int size) {
    s->points = (Coord*)malloc(size * sizeof(Point));
    s->top = -1;
    s->maxSize = size;
}

void push(Stack* s, Point p) {
    if (!isFull(s)) {
        s->points[++(s->top)] = p;
    }
}

Point pop(Stack* s) {
    return s->points[(s->top)--];
}

Point top(Stack* s) {
    return s->points[s->top];
}

Point nextToTop(Stack* s) {
    return s->points[s->top - 1];
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

int isFull(Stack* s) {
    return s->top == s->maxSize - 1;
}