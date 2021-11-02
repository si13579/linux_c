#include<stdio.h>
#include<stdlib.h>

#include<queue.h>

#define NAMESIZE	32
#define FNAME 	"/tmp/out"

struct node_st
{
	char data;
	struct node_st *l,*r;
};

void draw_(struct node_st *root,int level){
	int i;
	if(root == NULL)
		return ;
	draw_(root->r,level+1);
	for(i=0;i<level;i++)
		printf("    ");
	printf("%c\n",root->data);
	draw_(root->l,level+1);
}
void draw(struct node_st *root){
	draw_(root,0);
	printf("\n\n");
//	getchar();
}
struct node_st *load_(FILE *fp){
	int c;
	struct node_st *root;
	c = fgetc(fp);
	if(c != '('){
		fprintf(stderr,"fgetc():error.\n");
		exit(1);
	}
	c = fgetc(fp);
	if(c == ')')
		return NULL;
	root = malloc(sizeof(*root));
	if(root == NULL)
		exit(1);
	root->data = c;
//	printf("%d\n",c);
	root->l = load_(fp);
	root->r = load_(fp);
	fgetc(fp);

	return root;
}

struct node_st *load(const char *path){
	FILE *fp;
	struct node_st *root;
	fp = fopen(path,"r");
	if(fp == NULL){
		printf("ooo");
		return NULL;
	}
	root = load_(fp);
	fclose(fp);
	return root;
}

int main()
{
	struct node_st *root;

	root = load(FNAME);

	draw(root);
	exit(0);
}










