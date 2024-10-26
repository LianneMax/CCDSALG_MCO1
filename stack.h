#ifndef STACK_H
#define STACK_H

//typedef struct Point {
//    double x, y;
//} Point;

typedef struct Stack {
    Coord* points;
    int top;
    int maxSize;
} Stack;

void createStack(Stack* s, int size);
void push(Stack* s, Coord p);
Coord pop(Stack* s);
Coord top(Stack* s);
Coord nextToTop(Stack* s);
int isEmpty(Stack* s);
int isFull(Stack* s);

#endif