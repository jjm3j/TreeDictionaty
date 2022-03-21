#pragma once
#include <stdio.h>

struct stack
{
    struct node* data;
    struct stack* next;
};
struct stack* top;

void initStack(struct stack* top)
{
    top = NULL;
}


void push(struct stack* top, struct node* data)
{
    struct stack* tmp = (struct stack*)malloc(sizeof(struct stack));
    tmp->next = top;
    top = tmp;
    top->data = data;

}

void sort(struct stack* top)
{

}

void print(struct stack* s) {
    while (s) {
        cout << s->data << " ";
        s = s->next;
    }
}

int isEmpty (struct stack* top) {
    if (top == NULL) {
        return 1;
    }
    return 0;
}