#include<stdio.h>
#include<stdlib.h>
#include "llist.h"

#define NAMESIZE	32
struct score_st
{
	int id;
	char name[NAMESIZE];
	int math;
	int chinese;
};
static void print_s(const void *record){
	const struct score_st *r = record;
	printf("%d %s %d %d\n",r->id,r->name,r->math,r->chinese);
}

static int id_cmp(const void *key,const void *record){
	const int *k = key;
	const struct score_st *r = record;
	return (*k - r->id);
}
static int name_cmp(const void *key,const void *record){
	const char *k = key;
	const struct score_st *r = record;
	return strcmp(k,r->name);
}
int main(){
	LLIST *handler;
	
	struct score_st tmp;
	int ret,i;
	handler = llist_create(sizeof(struct score_st));
	if(handler == NULL)
		exit(1);
	for(i=0;i<7;i++){
		tmp.id = i;
		snprintf(tmp.name,NAMESIZE,"std%d",i);
		tmp.math = rand()%100;
		tmp.chinese = rand()%100;
		//ret = llist_insert(handler,&tmp,LLIST_FORWARD);
		ret = handler->insert(handler,&tmp,LLIST_BACKWARD);
		if(ret)
			exit(1);
	}

	handler->travel(handler,print_s);

#if 0
	printf("\n\n");
	char *del_name = "std6";
	ret = llist_delete(handler,del_name,name_cmp);
	if(ret)
		printf("llist_delete failed!\n");
	llist_travel(handler,print_s);

	int id = 30;
	
	struct score_st *data;
	data = llist_find(handler,&id,id_cmp);
	if(data == NULL)
		printf("Can not find!\n");
	else
		print_s(data);
#endif
	llist_destory(handler);

	exit(0);
}
