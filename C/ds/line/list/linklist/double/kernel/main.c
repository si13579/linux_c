#include<stdio.h>
#include<stdlib.h>
#include "list.h"
#define NAMESIZE	32
struct score_st
{
	int id;
	char name[NAMESIZE];
	struct list_head node;
	int math;
	int chinese;

};
static void print_s(struct score_st *d){
	printf("%d %s %d %d\n",d->id,d->name,d->math,d->chinese);
}
int main()
{
	struct score_st *datap;
	struct list_head *cur;
	LIST_HEAD(head);
	int i;
	
	for(i=0;i<7;i++){
		datap = malloc(sizeof(*datap));
		if(datap == NULL)
			exit(1);
		datap->id = i;
		snprintf(datap->name,NAMESIZE,"stu%d",i);
		datap->math = rand()%100;
		datap->chinese =rand()%100;
		list_add(&datap->node,&head);
	}

	__list_for_each(cur,&head){
		datap = list_entry(cur,struct score_st,node);
		print_s(datap);
	}
	

	__list_for_each(cur,&head){
		datap = list_entry(cur,struct score_st,node);
		if(datap->id == 15)
			break;	
	}
	if(cur == &head)
		printf("Can not find\n");
	else
		print_s(datap);
	




	exit(0);
}
