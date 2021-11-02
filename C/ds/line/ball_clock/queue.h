#ifndef QUEUE_H_
#define QUEUE_H_

#define MAXSIZE		32
typedef int datatype;
typedef struct
{
	datatype data[MAXSIZE];
	int head,tail;
}queue;

queue *qu_create();

int qu_isempty(queue *);

int qu_enqueue(queue *,datatype *);

int qu_dequeue(queue *,datatype *);

void qu_travel(queue *);

void  qu_clear(queue *);

void qu_destroy(queue *);






#endif
