//约定双方对话格式
#ifndef PROTO_H_
#define PROTO_H_

#define KEYPATH	"/etc/services"
#define	KEYPROJ	'g'

#define NAMESIZE	32

//约定传输内容的格式
struct msg_st
{
	long mtype;	//表示当前消息的类型
	char name[NAMESIZE];
	int math;
	int chinese;

};




#endif
