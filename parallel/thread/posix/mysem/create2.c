#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
static int num = 0;
static void *func(void *p)
{
	int i;
	num += 1;
	printf("num = %d, p = : %p\n",num,&i);
	while(1)
		pause();
	pthread_exit(NULL);
}
int main()
{
	int64_t i;
	int err;
	pthread_t tid;
	pthread_attr_t attr;
	
	pthread_attr_init(&attr);

	pthread_attr_setstacksize(&attr,1024L*1024L);

	for(i = 0; ; i++)
	{
		err = pthread_create(&tid,&attr,func,NULL);
		if(err)
		{
			fprintf(stderr,"pthread_create():%s\n",strerror(err));
			break;
		}
	}
	printf("%d\n",i);


	pthread_attr_destroy(&attr);
	exit(0);
}
