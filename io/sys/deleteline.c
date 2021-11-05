#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DELETELINE	2

int main(int argc,char *argv[])
{
	char *lineptr = NULL;
	size_t lines = 0;
	int count = 0;
	int pos;
	if(argc < 2){
		perror("Usage <file>");
		exit(1);
	}

	FILE *fp1 = NULL,*fp2 = NULL;
	fp1 = fopen(argv[1],"r");
	fp2 = fopen(argv[1],"r+");

	if(fp1 == NULL){
		perror("open()");
		exit(1);
	}

	if(fp2 == NULL){
		perror("open()");
		exit(1);
	}

	while(count != DELETELINE){
		getline(&lineptr,&lines,fp1);
		count++;
	}
	pos = ftell(fp1)-strlen(lineptr);
	while(1){
		if(getline(&lineptr,&lines,fp1) < 0)
			break;
		fseek(fp2,(long)pos,SEEK_SET);
		pos += strlen(lineptr);
		fwrite(lineptr,strlen(lineptr),1,fp2);
		printf("%s",lineptr);
	}
	int fd;
	fd = fileno(fp2);
	ftruncate(fd,pos);
	fclose(fp2);
	fclose(fp1);
	exit(0);
}

