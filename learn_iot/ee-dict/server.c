#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sqlite3.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <time.h>

//数据类型
enum {R=0,L,Q,H} t;

//消息传输结构体
typedef struct {
	int type;
	char name[20];
	char data[256];
}MSG;

//用户注册
void do_register(int newfd,MSG *msg,sqlite3 *db);
//用户登录
void do_login(int newfd,MSG *msg,sqlite3 *db);
//单词查询
void do_query(int newfd,MSG *msg,sqlite3 *db);
//文件中查询单词解释
int search(int newfd,char *word);
//历史记录查询
void do_history(int newfd,MSG *msg,sqlite3 *db);
//历史记录的回调函数
int history_callback(void *para,int f_num,char **f_value,char **f_name);


int main(int argc,char *argv[])
{
	if(argc < 3)
	{
		printf("Usage:%s <IP addr> <Port>\n",argv[0]);
		return 0;
	}
	//创建数据库
	sqlite3 *db;
	if(sqlite3_open("ee_dict.db",&db) != SQLITE_OK)
	{
		perror("sqlite3_open");
		exit(-1);
	}
#if 0
	//创建用户表和历史记录表
	char *errmsg;
	if(sqlite3_exec(db,"create table user(name char,passwd text);",NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
		exit(-1);
	}
#endif

	//创建套接字
	int fd;
	if((fd=socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		perror("socket");
		exit(-1);
	}
	//绑定套接字在指定地址
	struct sockaddr_in sin;
	bzero(&sin,sizeof(sin));
	sin.sin_family=AF_INET;
	sin.sin_port=htons(atoi(argv[2]));
	if(inet_pton(AF_INET,argv[1],&sin.sin_addr.s_addr) < 0)
	{
		perror("inet_pton");
		exit(-1);
	}
	if(bind(fd,(struct sockaddr *)&sin,sizeof(sin)) < 0)
	{
		perror("bind");
		exit(-1);
	}
	//监听套接字
	if(listen(fd,5) < 0)
	{
		perror("listen");
		exit(-1);
	}

	//处理僵尸进程
	signal(SIGCHLD,SIG_IGN);
	printf("server start ....\n");

	int newfd;
	pid_t pid=-1;
	while(1)
	{
		printf("wait client\n");
		//等待客户端连接
		if((newfd=accept(fd,NULL,NULL)) < 0)
		{
			perror("accept");
			exit(-1);
		}
		//创建子进程
		if((pid=fork()) < 0)
		{
			perror("fork");
			exit(-1);
		}
		else if(0 == pid)
		{
			printf("child process\n");
			close(fd);
			//子进程
			//接收来自客户端数据
			MSG msg;
			while(recv(newfd,&msg,sizeof(msg),0) > 0)
			{
				printf("type:%d\n",msg.type);
				//判断数据类型并处理
				switch(msg.type)
				{
					case R:
						do_register(newfd,&msg,db);
						break;
					case L:
						do_login(newfd,&msg,db);
						break;
					case Q:
						do_query(newfd,&msg,db);
						break;
					case H:
						do_history(newfd,&msg,db);
						break;
					default:
						printf("wrong type!\n");
				}
			}
			//关闭连接
			close(newfd);
			exit(0);
		}
		else
		{
			//父进程
			close(newfd);
		}
	}
	return 0;
}


//用户注册
void do_register(int newfd,MSG *msg,sqlite3 *db)
{
	//拼接SQL语句
	char sql[64];
	char *errmsg;
	MSG ret_msg;
	ret_msg.type=msg->type;
	strcpy(ret_msg.name,msg->name);
	bzero(ret_msg.data,sizeof(ret_msg.data));
	//拼接注册信息的SQL语句
	sprintf(sql,"insert into user values('%s','%s');",msg->name,msg->data);
	printf("sql:%s\n",sql);
	//将用户信息写入user数据表
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		//失败发送失败提示
		strcpy(ret_msg.data,"register failed");
	}
	else
	{
		//成功发送成功提示
		strcpy(ret_msg.data,"register success");
	}
	//发送注册信息给客户端
	if(send(newfd,&ret_msg,sizeof(ret_msg),0) < 0)
	{
		perror("send");
		exit(-1);
	}
}

//用户登录
void do_login(int newfd,MSG *msg,sqlite3 *db)
{
	//拼接SQL语句
	char sql[64];
	char *errmsg;
	MSG ret_msg;
	ret_msg.type=msg->type;
	strcpy(ret_msg.name,msg->name);
	bzero(ret_msg.data,sizeof(ret_msg.data));
	//拼接用户表查询SQL语句
	sprintf(sql,"select * from user where name='%s' and passwd='%s';",msg->name,msg->data);
	printf("sql:%s\n",sql);
	//查询用户是否存在于user数据表
	char **presult;
	int nrow,ncol;
	if(sqlite3_get_table(db,sql,&presult,&nrow,&ncol,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
		exit(-1);
	}
	else
	{
		printf("nrow:%d\n",nrow);
		if(nrow == 1)
		{
			//成功发送成功提示
			strcpy(ret_msg.data,"yes");
		}
		else
		{
			//失败发送失败提示
			strcpy(ret_msg.data,"no");
		}
	}
	//发送登录信息查询结果给客户端
	if(send(newfd,&ret_msg,sizeof(ret_msg),0) < 0)
	{
		perror("send");
		exit(-1);
	}

}

//单词查询
void do_query(int newfd,MSG *msg,sqlite3 *db)
{
	if(1 == search(newfd,msg->data))
	{
		//如果查询成功则添加到历史记录
		//获取系统当前时间
		char record_time[20];
		time_t t;
		struct tm *tnow;
		char sql[64];
		char *errmsg;
		t=time(0);
		tnow=localtime(&t);
		sprintf(record_time,"%4d-%2d-%2d %2d:%2d:%2d",tnow->tm_year+1900,tnow->tm_mon+1,tnow->tm_mday,tnow->tm_hour,tnow->tm_min,tnow->tm_sec);
		
		//拼接SQL语句
		sprintf(sql,"insert into record values('%s','%s','%s');",msg->name,msg->data,record_time);
		//将查询人名称、查询的词和查询的时间都写入记录表
		if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
		{
			printf("%s\n",errmsg);
			exit(-1);
		}
		else
		{
			printf("record a word.\n");
		}

	}
	else
	{
		//如果查询失败则返回提示信息
		strcpy(msg->data,"No this word");
		if(send(newfd,msg,sizeof(*msg),0) < 0)
		{
			perror("send");
			exit(-1);
		}
	}
	
}

//文件中查询单词解释
int search(int newfd,char *word)
{
	//打开字典文件
	FILE *f;
	if((f=fopen("dict.txt","r")) == NULL)
	{
		perror("fopen");
		exit(-1);
	}
	//在字典中查询单词
	char buf[256];
	MSG ret_msg;
	bzero(buf,sizeof(buf));
	printf("word:%s",word);
	//使用行读取方式查看词典
	while(fgets(buf,sizeof(buf)-1,f) != NULL)
	{
		printf("data:%s",buf);
		//找到对应单词,找到对应的词，这个词语必须字母一致且没有多余后缀
		if((strncmp(buf,word,strlen(word)) == 0) && (buf[strlen(word)] == ' '))
		{
			//优化查询结果
			char *p;
			p = buf+strlen(word);
			while(*p == ' ')
			{
				p++;
			}
			strcpy(ret_msg.data,p);
			if(send(newfd,&ret_msg,sizeof(ret_msg),0) < 0)
			{
				perror("send");
				exit(-1);
			}
			return 1;
		}
	}

	//关闭字典文件
	fclose(f);
	return 0;
}

//历史记录查询
void do_history(int newfd,MSG *msg,sqlite3 *db)
{
	//拼接SQL语句
	char sql[64];
	char *errmsg;
	MSG ret_msg;
	sprintf(sql,"select * from record where name='%s';",msg->name);
	printf("sql:%s\n",sql);
	//从数据库中查找数据
	if(sqlite3_exec(db,sql,history_callback,&newfd,&errmsg) != SQLITE_OK)
	{
		printf("No such record.\n");
		printf("%s\n",errmsg);
		exit(-1);
	}
	printf("record is found.\n");
	strcpy(ret_msg.data,"All record over!");
	//无论是否有历史记录都发送一个结束反馈信息给客户端
	if(send(newfd,&ret_msg,sizeof(ret_msg),0) < 0)
	{
		perror("send");
		exit(-1);
	}
}

//历史记录的回调函数
int history_callback(void *para,int f_num,char **f_value,char **f_name)
{
	//处理历史记录
	MSG ret_msg;
	char buf[256];
	int newfd=*(int *)para;
	//查看所有存在的历史记录
	for(int i=0;i<f_num;i+=3)
	{
		bzero(buf,sizeof(buf));
		//printf("history:%-11s \n",f_value[i]);
		sprintf(buf,"%-11s %-11s %-11s",f_value[i],f_value[i+1],f_value[i+2]);
		strcpy(ret_msg.data,buf);
		//发送所有历史记录到客户端
		if(send(newfd,&ret_msg,sizeof(ret_msg),0) < 0)
		{
			perror("send");
			exit(-1);
		}
	}
	return 0;
}

