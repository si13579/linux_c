#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

static void *func(void *p)
{
	puts("Thread is working");
	pthread_exit(NULL);
	//return NULL
}
int main()
{
	pthread_t tid;
	int err;
	puts("Begin!");

	err = pthread_create(&tid,NULL,func,NULL);
	if(err){
		fprintf(stderr,"pthread_create():%s\n",strerror(err));
		exit(1);
	}

	pthread_join(tid,NULL);   //收尸等的动作相当于等待我创建出去的线程一定运行完

	puts("End!");
	exit(0);
}
