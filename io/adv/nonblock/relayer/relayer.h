#ifndef RELAYER_H_
#define RELAYER_H_

#define REL_JOBMAX	10000

enum
{
	STATE_RUNNING=1,	//正常运行态
	STATE_CANCELED,		//取消
	STATE_OVER	
};


struct rel_stat_st //任务状态结构体
{
	int state;
	int fd1;
	int fd2;
	int64_t count12,count21;	//设备对话字节数
//	struct timerval start,end;	//任务开始，结束时间
};

int rel_addjob(int fd1,int fd2);    //数组中添加任务
/*
 * return	>=	0			成功，返回当前任务ID
 * 			==	-EINVAL		失败，参数非法
 * 			==	-ENOSPAC	失败，任务数组满
 * 			==	-ENOMEM		失败，内存分配有误
 */

int rel_canceljob(int id);	//数组中取消任务
/*
 * 	return	==	0			成功，指定任务成功取消
 * 			==	-EINVAL		失败，参数非法
 * 			==	-EBUSY		失败，任务早已被取消
 */

int rel_waitjob(int id,struct rel_stat_st *);	//收尸
/*
 * 	return	==	0		成功，指定任务已终止，并返回状态
 * 			==	-EINVAL	失败，参数非法
 */

int rel_statjob(int id,struct rel_stat_st *);	//获取当前任务状态
/*
 * 	return	==	0		成功，指定任务状态已经返回
 * 			==	-EINVAL	失败，参数非法
 */




#endif
