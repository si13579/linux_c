#include<stdio.h>
#include<stdlib.h>
#include<termios.h>

int main()
{
	int ch;
	struct termios new,old;
	tcgetattr(0,&new);
	tcgetattr(0,&old);
	new.c_lflag = new.c_lflag & ~(ICANON | ECHO);//激活终端并关闭回显属性
	new.c_cc[VMIN] = 1; //最少一次要接收几个字符
	new.c_cc[VTIME] = 0;//时间
	tcsetattr(0,TCSANOW,&new);
	while(1)
	{
		
		ch = getchar();
		if(ch == 'Q')
			break;
		printf("%x ",ch);
		fflush(NULL);
	}
	tcsetattr(0,TCSANOW,&old);










	return 0;
}
