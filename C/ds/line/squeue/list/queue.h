#ifndef QUEUE_H_
#define QUEUE_H_

#include "llist.h"

typedef LLIST QUEUE;

QUEUE *queue_create(int);

int queue_en(QUEUE *,const void *);

int queue_de(QUEUE *,void *);

void queue_destory(QUEUE *);



#endif
