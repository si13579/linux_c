#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DESC_SIZE	256
#define KEY_SIZE	256
#define	BUFSIZE		512
#define FNAME	"log"

struct node_st
{
	struct node_st *ch[26];
	char desc[DESC_SIZE];
};

int get_word(FILE *fp,char *key,char *desc){
	int i,j;
	char buf[BUFSIZE];
	char *retp;
	retp = fgets(buf,BUFSIZE,fp);
	if(retp == NULL)
		return -1;
	for(i = 0; i < KEY_SIZE-1 && buf[i] != ':'; i++)
		key[i] = buf[i];
	key[i] = '\0';
	i++;
	for(j = 0;j < DESC_SIZE - 1 && buf[i] != '\0';j++,i++)
		desc[j] = buf[i];
	desc[j] = '\0';

	return 0;

}

struct node_st *newnode(void){
	int i;
	struct node_st *node;
	node = malloc(sizeof(*node));
	if(node == NULL)
		return NULL;

	node->desc[0] = '\0';
	for(i=0;i<26;i++)
		node->ch[i] = NULL;
	return node;
}

int insert(struct node_st **root,char *key,char *desc){
	if(*root == NULL){
		*root = newnode();
		if(*root == NULL)
			return -1;
	}
	if(*key == '\0'){
		strcpy((*root)->desc,desc);
		return 0;
	}
	return insert((*root)->ch + *key-'a',key+1,desc);


}


char *find(struct node_st *root,char *key){
	if(root == NULL)
		return NULL;
	if(*key == '\0')
		return root->desc;
	return find(root->ch[*key-'a'],key+1);
}

int main(){
	
	struct node_st *tree = NULL;
	FILE *fp;
	int ret;
	char desc[DESC_SIZE],key[KEY_SIZE];
	char *datap;
	fp = fopen(FNAME,"r");
	if(fp == NULL){
		fprintf(stderr,"fopen():error!");
		exit(1);
	}

	while(1){
		ret = get_word(fp,key,desc);
		if(ret == -1)
			break;
		insert(&tree,key,desc);
	}

	datap = find(tree,"donkeyabc");
	if(datap == NULL)
		printf("Can not find!\n");
	else
		puts(datap);


	fclose(fp);



	exit(0);
}
