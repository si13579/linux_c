#ifndef ANYTIMER_H_
#define ANYTIMER_H_

#define JOB_MAX	1024
typedef void at_jobfunc_t(void *);

int at_addjob(int sec,at_jobfunc_t *jobp,void *arg);
/* 
 *	return >= 0 成功，返回任务ID
 *		== -EINVAL 失败，参数非法
 *		== -ENOSPC	失败，数组满
 *		== -ENOMEM	失败，内存空间不足
 */


int at_canceljob(int id);
/*
 * return == 0	成功，指定任务成功取消
 * 		  == -EINVAL	失败，参数非法
 * 		  == -EBUSY		失败，指定任务已完成
 * 		  == -EACNCELED	失败，指定任务重复取消
*/

int at_waitjob(int id);
/*
 * return == 0	成功，指定任务成功释放
 * 		  == -EINVAL	失败，参数非法
 */




#endif
