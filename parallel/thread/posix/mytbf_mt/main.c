//令牌桶
#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<signal.h>
#include<string.h>

#include "mytbf.h"
#define CPS		10
#define BUFSIZE	1024
#define BURST	100

int main(int argc,char *argv[])
{
	char buf[BUFSIZE];
	int sfd,dfd = 1;
	int len,ret,pos;
	mytbf_t *tbf;
	int size;
	if(argc < 2){
		fprintf(stderr,"Usage...\n");
		exit(1);
	}

	tbf = mytbf_init(CPS,BURST);
	if(tbf == NULL)
	{
		fprintf(stderr,"mytbf_init() failed!\n");
		exit(1);
	}

	do
	{
	sfd = open(argv[1],O_RDONLY);
	if(sfd < 0){
		if(errno != EINTR)
		{
		perror("open()");
		exit(1);
		}
	}
	}while(sfd < 0);

	
	while(1){
		size = mytbf_fetchtoken(tbf,BUFSIZE);
		if(size < 0)
		{
			fprintf(stderr,"mytbf_fetchtoken():%s\n",strerror(-size));
			exit(1);
		}

		while((len = read(sfd,buf,size)) < 0)
		{
			if(errno == EINTR)
				continue;
			perror("read()");
			break;
		}
		if(len == 0)
			break;

		if(size - len > 0)
			mytbf_returntoken(tbf,size-len);
		pos = 0;
		while(len > 0){
			ret = write(dfd,buf+pos,len);
			if(ret < 0){
				perror("write()");
				exit(1);
			}
			pos += ret;
			len -= ret;
		}
		//sleep(1);
	}

	close(sfd);

	mytbf_destory(tbf);
	exit(0);
	}
