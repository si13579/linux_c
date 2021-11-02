#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE *fp;
	fp = fopen("tmp");
	if(fp == NULL){
		fprintf(stderr,"fopen(): failed!errno = %d\n",errno);
		exit(1);
	}

	puts("OK");







	exit(0);
}
