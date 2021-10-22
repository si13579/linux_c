#include<stdio.h>
#include<stdlib.h>

#define JOS_NR	8
struct node_st{
	int data;
	struct node_st *next;
};

struct node_st *jose_create(int n){
	struct node_st *me,*newnode,*cur;
	int i =1;
	me = malloc(sizeof(*me));
	if(me == NULL)
		return NULL;

	me->data = i;
	me->next = me;
	i++;
	for(cur = me;i<=n;i++){
		newnode = malloc(sizeof(*newnode));
		if(newnode == NULL)
			return NULL;
		newnode->data = i;
		newnode->next =me;
		cur->next = newnode;
		cur=newnode;
	}
	return me;
}
void jose_show(struct node_st *me){
	struct node_st *cur;
	for(cur = me; cur->next != me;cur=cur->next)
		printf("%d ",cur->data);
	printf("%d\n",cur->data);
}

void jose_kill(struct node_st **me,int n){
	struct node_st *cur = *me,*node;
	int i = 1;
	while(cur != cur->next){
	while(i < n){
		node = cur;
		cur = cur->next;
		i++;
	}
	printf("%d ",cur->data);
	node->next  = cur->next;
	free(cur);
	cur = node->next;
	i = 1;
	}
	printf("\n");
	*me = cur;
}
int main(){
	struct node_st *list;
	
	int n = 3;

	list = jose_create(JOS_NR);
	if(list == NULL)
		exit(1);
	jose_show(list);

	jose_kill(&list,n);
	
	jose_show(list);




	exit(0);
};
