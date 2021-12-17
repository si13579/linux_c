#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#define	LEFT	30000000
#define	RIGHT	30000200
#define THRNUM	4


static int num = 0;

static pthread_mutex_t mut_num = PTHREAD_MUTEX_INITIALIZER;

static void * thr_primer(void *p);

int main()
{
	int i,err;
	pthread_t tid[THRNUM];

	for(i = 0; i <= THRNUM;i++)
	{
		err = pthread_create(tid+i,NULL,thr_primer,(void *)i);
		if(err)
		{
			fprintf(stderr,"pthread_create():%s\n",strerror(err));
			exit(1);
		}
	}	

	for(i = LEFT; i <= RIGHT; i++)
	{
		pthread_mutex_lock(&mut_num);
		while(num != 0)
		{
			pthread_mutex_unlock(&mut_num);
			sched_yield();//出让调度器给别的线程，可以理解成非常短的sleep，而且不会引起调度颠簸
			pthread_mutex_lock(&mut_num);
		}
		num = i;
		pthread_mutex_unlock(&mut_num);
	}

	pthread_mutex_lock(&mut_num);
	while(num != 0)
	{
		pthread_mutex_unlock(&mut_num);
		sched_yield();
		pthread_mutex_lock(&mut_num);
	}
	num = -1;
	pthread_mutex_unlock(&mut_num);


	for(i = 0; i < THRNUM; i++)
		pthread_join(tid[i],NULL);

	pthread_mutex_destroy(&mut_num);
	exit(0);
}

static void *thr_primer(void *p)
{
	int i,j,mark;
	while(1)
	{
		pthread_mutex_lock(&mut_num);
		while(num == 0)
		{
			pthread_mutex_unlock(&mut_num);
			sched_yield();
			pthread_mutex_lock(&mut_num);
		}
		if(num == -1){	//临界区跳转一定要解锁再跳转
			pthread_mutex_unlock(&mut_num);
			break;
		}
		i = num;
		num = 0;
		pthread_mutex_unlock(&mut_num);

		mark = 1;
		for(j = 2; j < i/2; j++)
		{
			if(i % j == 0){
				mark = 0;
				break;
			}
		}
		if(mark)
			printf("[%d]%d id a primer\n",(int)p,i);
	}
	pthread_exit(NULL);
}
