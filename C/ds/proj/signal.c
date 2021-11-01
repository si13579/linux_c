#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
void alrm_handler(int s){
	alarm(1);
	printf("get SIGALRM\n");
}
int main()
{

	int ch;
	signal(SIGALRM,alrm_handler);
	alarm(1);
	while(1){
		ch = getchar();
		printf("ch = %x\n",ch);
	}


	return 0;
}
