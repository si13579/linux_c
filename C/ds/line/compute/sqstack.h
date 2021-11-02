#ifndef SQSTACK_H_
#define SQSTACK_H_

#define MAXSIZE		32
typedef int datatype;
typedef struct node_st
{
	datatype data[MAXSIZE];
	int top;
}sqstack;

sqstack *st_create(void);

int st_isempty(sqstack *);


int st_push(sqstack *,datatype *);

int st_pop(sqstack *,datatype *);

int st_top(sqstack *,datatype *);

void st_travel(sqstack *);
void st_destory(sqstack *);













#endif
