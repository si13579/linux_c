#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<pthread.h>

#include "mytbf.h"

static struct mytbf_st * job[MYTBF_MAX];
static pthread_mutex_t mut_job = PTHREAD_MUTEX_INITIALIZER;//静态初始化互斥量

static pthread_t tid_alrm;

static pthread_once_t init_once = PTHREAD_ONCE_INIT;
static int inited = 0;


//typedef void (*sighandler_t)(int);
//static sighandler_t alrm_handler_save;
struct mytbf_st
{
	int cps;
	int burst;
	int token;
	int pos;
	pthread_mutex_t mut;
	pthread_cond_t cond;
};


static void *thr_alrm(void *p) //作为一个线程，返回值是void *
{
	int i;

	//	alarm(1);
	while(1)
	{

		pthread_mutex_lock(&mut_job);
		for(i = 0; i < MYTBF_MAX; i++)
		{
			if(job[i] != NULL)
			{
				pthread_mutex_lock(&job[i]->mut);
				job[i]->token += job[i]->cps;
				if(job[i]->token > job[i]->burst)
					job[i]->token = job[i]->burst;
				pthread_cond_broadcast(&job[i]->cond);
				pthread_mutex_unlock(&job[i]->mut);
			}

		}
		pthread_mutex_unlock(&mut_job);
		sleep(1);
	}
}
static void module_unload(void)//有一个线程调用，多个线程调用会出错
{
	int i;
//	signal(SIGALRM,alrm_handler_save);
//	alarm(0);


	pthread_cancel(tid_alrm);
	pthread_join(tid_alrm,NULL);

	for(i = 0; i < MYTBF_MAX;i++)
	{
		if(job[i] != NULL)
		{
			mytbf_destory(&job[i]);	
		}
	}
	pthread_mutex_destroy(&mut_job);
}
static void module_load(void)
{
	//	alrm_handler_save = signal(SIGALRM,alrm_handler);
	//	alarm(1);
//	pthread_t tid_alrm;
	int err;

	err = pthread_create(&tid_alrm,NULL,thr_alrm,NULL);
	if(err){
		fprintf(stderr,"pthread_create():%s\n",strerror(err));
		exit(1);
	}
	atexit(module_unload);
}

static int get_free_pos_unlocked(void) //用该函数先加锁再调函数
{
	int i;
	for(i = 0; i < MYTBF_MAX; i++)
	{
		if(job[i] == NULL)
			return i;
	}
	return -1;

}

mytbf_t *mytbf_init(int cps,int burst)
{
	struct mytbf_st *me;
	int pos;
	/*
	if(!inited){
		//	signal(SIGALRM,);
		//	alarm(1);
		module_load();
		inited = 1;
	}
	*/
	pthread_once(&init_once,module_load);

	pthread_mutex_lock(&mut_job);

	me = malloc(sizeof(*me));
	if(me == NULL)
		return NULL;
	me->token = 0;
	me->cps = cps;
	me->burst = burst;
	pthread_mutex_init(&me->mut,NULL);
	pthread_cond_init(&me->cond,NULL);
	pos = get_free_pos_unlocked(); //从数组当中找空位
	//临界区
	if(pos < 0)//临界区跳转语句需要注意
	{
		pthread_mutex_unlock(&mut_job);
		free(me);
		return NULL;
	}
	me->pos = pos;
	job[pos] = me;
	//临界区
	pthread_mutex_unlock(&mut_job);

	return me;
}

static int min(int a,int b){
	return a < b ? a : b;
}

int mytbf_fetchtoken(mytbf_t *ptr,int size){
	struct mytbf_st *me = ptr;
	int n;
	if(size <= 0)
		return -EINVAL;

	pthread_mutex_lock(&me->mut);
	while(me->token <= 0)
	{
		pthread_cond_wait(&me->cond,&me->mut);//发现条件不成立，解锁me->mut，等待
	/*
		pthread_mutex_unlock(&me->mut);
		sched_yield();//短暂出让调度器
		pthread_mutex_lock(&me->mut);
	*/
	}
	n = min(me->token,size);

	me->token -= n;

	pthread_mutex_unlock(&me->mut);

	return n;
}
int mytbf_returntoken(mytbf_t *ptr,int size){

	struct mytbf_st *me = ptr;

	if(size <= 0)
		return -EINVAL;

	pthread_mutex_lock(&me->mut);
	me->token += size;
	if(me->token > me->burst)
		me->token = me->burst;
	pthread_cond_broadcast(&me->cond);
	pthread_mutex_unlock(&me->mut);


	return size;
}

int mytbf_destory(mytbf_t *ptr){
	struct mytbf_st *me = ptr;

	pthread_mutex_lock(&mut_job);
	job[me->pos] = NULL;
	pthread_mutex_unlock(&mut_job);

	pthread_mutex_destroy(&me->mut);
	pthread_cond_destroy(&me->cond);
	free(ptr);

	return 0;
}

