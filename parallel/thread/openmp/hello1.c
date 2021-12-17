#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
int main()
{
#pragma omp parallel sections	//以段落为单位来进行并发
	{
#pragma omp section //第一个段落
	printf("[%d]Hello\n",omp_get_thread_num());  //打印线程标识
#pragma omp section	//第二个段落
	printf("[%d]World\n",omp_get_thread_num());
	}
	exit(0);
	
}
