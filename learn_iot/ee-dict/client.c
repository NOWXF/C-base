#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <sqlite3.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//请求类型
enum {R=0,L,Q,H} t;

//数据传输结构
typedef struct{
	int type;
	char name[20];
	char data[256];    //用于传输密码或者要查询的单词
}MSG;

void do_register(int fd);
int do_login(int fd,MSG *msg);
void do_query(int fd,MSG *msg);
void do_history(int fd,MSG *msg);


int main(int argc,char *argv[])
{
	MSG msg;
	//判断运行程序
	if(argc < 3)
	{
		printf("Usage:./client <IP addr> <Port>\n");
		return 0;
	}
	//创建套接字
	int fd;
	if((fd=socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		perror("socket");
		exit(-1);
	}
	//连接服务器
	struct sockaddr_in sin;
	bzero(&sin,sizeof(sin));
	sin.sin_family=AF_INET;
	sin.sin_port=htons(atoi(argv[2]));
	if(inet_pton(AF_INET,argv[1],&sin.sin_addr.s_addr) < 0)
	{
		perror("inet_pton");
		exit(-1);
	}
	if(connect(fd,(struct sockaddr *)&sin,sizeof(sin)) < 0)
	{
		perror("connect");
		exit(-1);
	}
	//显示入口菜单
	int cmd=0;
	while(1)
	{
		printf("********************************************\n");
		printf("*1.注册            2.登录            3.退出*\n");
		printf("********************************************\n");
		printf("请输入选择：");
		scanf("%d",&cmd);
		while(getchar()!='\n');
		switch(cmd)
		{
			case 1:
				do_register(fd);
				break;
			case 2:
				if(1 == do_login(fd,&msg))
					goto page2;
				break;
			case 3:
				close(fd);
				exit(0);
				break;
			default:
				printf("您输入的命令有误，请重新输入！\n");
				break;
		}
	}
	//显示功能菜单
page2:while(1)
	  {
		  printf("********************************************\n");
		  printf("*1.查询单词        2.历史记录        3.退出*\n");
		  printf("********************************************\n");
		  printf("请输入选择：");
		  scanf("%d",&cmd);
		  while(getchar()!='\n');
		  switch(cmd)
		  {
			  case 1:
				  do_query(fd,&msg);
				  break;
			  case 2:
				  do_history(fd,&msg);
				  break;
			  case 3:
				  close(fd);
				  exit(-1);
				  break;
			  default:
				  printf("您输入的选项有误,请您重新输入!\n");
				  break;
		  }
	 }
	return 0;
}

//注册函数
void do_register(int fd)
{
	MSG msg;
	msg.type=R;
	bzero(msg.data,sizeof(msg.data));
	//录入注册信息
	printf("请输入您的姓名：");
	scanf("%s",msg.name);
	printf("请输入您的密码：");
	scanf("%s",msg.data);
	//发送注册信息给服务器
	if(send(fd,&msg,sizeof(msg),0) < 0)
	{
		perror("send");
		exit(-1);
	}
	//接收来自服务器的反馈信息
	MSG rec_msg;
	if(recv(fd,&rec_msg,sizeof(rec_msg),0) < 0)
	{
		perror("recv");
		exit(-1);
	}
	printf("%s\n",rec_msg.data);
}


//登录函数
int do_login(int fd,MSG *msg)
{
	msg->type=L;
	bzero(msg->data,sizeof(*(msg->data)));
	//填写登录信息
	printf("请输入您的姓名：");
	scanf("%s",msg->name);
	printf("请输入您的密码：");
	scanf("%s",msg->data);
	//发送登录信息给服务器
	if(send(fd,msg,sizeof(*msg),0) < 0)
	{
		perror("send");
		exit(-1);
	}
	//服务器反馈是否登录
	MSG rec_msg;
	if(recv(fd,&rec_msg,sizeof(rec_msg),0) < 0)
	{
		perror("recv");
		exit(-1);
	}
	printf("%s\n",rec_msg.data);
	//比较返回值结果
	if(strncmp(rec_msg.data,"yes",3) == 0)
	{
		printf("login success!!\n");
		return 1;
	}
	else
	{
		printf("login failed!!\n");
		return 0;
	}
}

//查询单词函数
void do_query(int fd,MSG *msg)
{
	while(1)
	{
		msg->type=Q;
		bzero(msg->data,sizeof(*(msg->data)));
		//录入要查询的单词
		printf("请输入您要查询的单词：");
		scanf("%s",msg->data);
		if(strncmp(msg->data,"#",1) == 0)
		{
			break;
		}

		//发送查询信息给服务器
		if(send(fd,msg,sizeof(*msg),0) < 0)
		{
			perror("send");
			exit(-1);
		}
		//接收服务器返回的查询结果
		MSG rec_msg;
		if(recv(fd,&rec_msg,sizeof(rec_msg),0) < 0)
		{
			perror("recv");
			exit(-1);
		}
		printf("%s\n",rec_msg.data);
	}	
}

//历史记录函数
void do_history(int fd,MSG *msg)
{
	msg->type=H;
	bzero(msg->data,sizeof(*(msg->data)));
	//发送历史记录查询请求
	if(send(fd,msg,sizeof(*msg),0) < 0)
	{
		perror("send");
		exit(-1);
	}
	//接收来自服务器的结果
	MSG rec_msg;
	int ret=-1;
	while((ret=recv(fd,&rec_msg,sizeof(rec_msg),0)) > 0)
	{
		printf("%s\n",rec_msg.data);
		if(strncmp(rec_msg.data,"All record over!",16) == 0)
			break;
	}
	if(ret < 0)
	{
		perror("recv");
		exit(-1);
	}
}
