#include<stdio.h>
#include<stdlib.h>

int main()
{
//	char str[] = "123456";

//	printf("%d\n",atoi(str));
	
	int year = 2014,month = 5,day = 13;
	char buf[1024];
	sprintf(buf,"%d-%d-%d",year,month,day);
	puts(buf);




	exit(0);
}
