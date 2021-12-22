//有限状态机编程实例
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>


#define BUFSIZE	1024
#define TTY1	"/dev/tty11"
#define TTY2	"/dev/tty12"

enum
{
	STATE_R = 1, //读态
	STATE_W,	//写态
	STATE_Ex,	//异常态
	STATE_T		//终止态
};

struct fsm_st //有限状态机
{
	int state;//状态
	int sfd; //源文件文件描述符
	int dfd; //目标文件描述符
	int len;
	int pos;
	char buf[BUFSIZE];
	char *errstr; //出错的字符串
};

static void fsm_driver(struct fsm_st *fsm) //实现状态机的推动
{
	int ret;
	switch(fsm->state)
	{
		case STATE_R: //读态
			fsm->len = read(fsm->sfd,fsm->buf,BUFSIZE);
			if(fsm->len == 0) //读完结束
				fsm->state = STATE_T;
			else if(fsm->len < 0) //失败
			{
				if(errno == EAGAIN) //假错没读到
					fsm->state = STATE_R;
				else 		//真错，异常终止
				{
					fsm->errstr = "read()";
					fsm->state = STATE_Ex;
				}
			}
			else //读到去写态
			{
				fsm->pos = 0;
				fsm->state = STATE_W;
			}

			break;
		case STATE_W:
			ret = write(fsm->dfd,fsm->buf+fsm->pos,fsm->len);
			if(ret < 0) //失败
			{
				if(errno = EAGAIN)
					fsm->state = STATE_W;
				else
				{
					fsm->errstr = "write()";
					fsm->state = STATE_Ex;
				}
			}
			else
			{
				fsm->pos += ret;
				fsm->len -= ret;
				if(fsm->len == 0) //写完去读态
					fsm->state = STATE_R;
				else	//没写完继续去写
					fsm->state = STATE_W;
			}
			break;
		case STATE_Ex:
			perror(fsm->errstr);
			fsm->state = STATE_T;
			break;
		case STATE_T:
			//do something
			break;
		default:
			abort();
			break;
	}	

}


static void relay(int fd1,int fd2)
{
	int fd1_save,fd2_save;
	struct fsm_st fsm12,fsm21;//读左写右，读右写左
	//保证是以非阻塞方式实现的
	fd1_save = fcntl(fd1,F_GETFL); //获取文件属性
	fcntl(fd1,F_SETFL,fd1_save|O_NONBLOCK);

	fd2_save = fcntl(fd2,F_SETFL);
	fcntl(fd2,F_SETFL,fd2_save|O_NONBLOCK);

	fsm12.state = STATE_R;
	fsm12.sfd = fd1;
	fsm12.dfd = fd2;
	fsm21.state = STATE_R;
	fsm21.sfd = fd2;
	fsm21.dfd = fd1;

	while(fsm12.state != STATE_T || fsm21.state != STATE_T)
	{
		//布置监视任务
		//监视
		select();
		//查看监视结果

		//根据监视结构来有条件的推动状态机
		if()
		fsm_driver(&fsm12);
		if()
		fsm_driver(&fsm21);
	}
	fcntl(fd1,F_SETFL,fd1_save); //恢复文件属性
	fcntl(fd2,F_SETFL,fd2_save);


}


int main()
{
	int fd1,fd2;
	fd1 = open(TTY1,O_RDWR);
	if(fd1 < 0)
	{
		perror("open()");
		exit(1);
	}
	write(fd1,"TTY1\n",5);
	fd2 = open(TTY2,O_RDWR|O_NONBLOCK);
	if(fd2 < 0)
	{
		perror("open()");
		exit(1);
	}
	write(fd2,"TTY2\n",5);

	relay(fd1,fd2);
	close(fd2);
	close(fd1);




	exit(0);
}
