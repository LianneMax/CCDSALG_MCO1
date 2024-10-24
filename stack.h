//stack.h
#ifndef STACK_H
#define STACK_H

typedef struct Stack {
    Point* points;
    int top;
    int maxSize;
} Stack;

void createStack(Stack* s, int size);
void push(Stack* s, Point p);
Point pop(Stack* s);
Point top(Stack* s);
Point nextToTop(Stack* s);
int isEmpty(Stack* s);
int isFull(Stack* s);

#endif