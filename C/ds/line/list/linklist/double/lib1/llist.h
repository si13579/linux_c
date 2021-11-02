#ifndef LLIST_H_
#define LLIST_H_

#define LLIST_FORWARD	1
#define LLIST_BACKWARD	2

typedef void llist_op(const void *);
typedef int llist_cmp(const void *,const void *);
struct llist_node_st
{
	void *data;
	struct llist_node_st *prev;
	struct llist_node_st *next;
};

typedef struct
{
	int size;
	struct llist_node_st head;
}LLIST;


LLIST *llist_create(int initsize);

int llist_insert(LLIST *,const void *data,int mode);


void *llist_find(LLIST *,const void *key,llist_cmp *);

int llist_delete(LLIST *,const void *key,llist_cmp *);

int llist_fetch(LLIST *,const void *key,llist_cmp *,void *data);

void llist_travel(LLIST *,llist_op *);
//void llist_travel(LLIST *,void (*)(const void *));


void llist_destory(LLIST *);





#endif
