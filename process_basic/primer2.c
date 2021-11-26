#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#define	LEFT	30000000
#define	RIGHT	30000200
int main()
{
	pid_t pid;
	int i,j,mark;
	for(i = LEFT; i <= RIGHT; i++)
	{
		pid = fork();
		if(pid < 0){
			perror("fork()");
			exit(1);
		}
		if(pid == 0){ 	//child
			mark = 1;
			for(j = 2; j < i/2; j++)
			{
				if(i % j == 0){
					mark = 0;
					break;
				}
			}
			if(mark)
				printf("%d id a primer\n",i);
			exit(0);
		}
	}

//	int st;
	for(i = LEFT; i <= RIGHT; i++){
//		wait(&st);
		wait(NULL);
	} 



	exit(0);
}
