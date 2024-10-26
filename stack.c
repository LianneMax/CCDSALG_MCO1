// stack.c
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "sort.h"

void createStack(Stack* s, int size) {
    s->points = (Coord*)malloc(size * sizeof(Coord));
    s->top = -1;
    s->maxSize = size;
}

void push(Stack* s, Coord p) {
    if (!isFull(s)) {
        s->points[++(s->top)] = p;
    }
}

Coord pop(Stack* s) {
    return s->points[(s->top)--];
}

Coord top(Stack* s) {
    return s->points[s->top];
}

Coord nextToTop(Stack* s) {
    return s->points[s->top - 1];
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

int isFull(Stack* s) {
    return s->top == s->maxSize - 1;
}
