#ifndef STACK_H__
#define STACK_H__

#include "llist.h"

typedef LLIST STACK;

STACK *stack_create(int);

int stack_push(STACK *ptr, const void *data);

int stack_pop(STACK *ptr, void *data);

void stack_travel();

void stack_destory(STACK *st);

#endif /* STACK_H__ */