#ifndef STACK_H_
#define STACK_H_
#include "llist.h"

typedef LLIST STACK;

STACK *stack_create();

int stack_push(STACK *,const void *data);

int stack_pop(STACK *,void *data);



void stack_destory(STACK *);









#endif
