#include "net.h"

#define SOCK_ADDR "127.0.0.1"
#define SOCK_PORT 5001

int main(int argc,char **argv)
{
	int sfd;
	struct sockaddr_in sin;
	if(argc < 3)
	{
		printf("usage:./client IP_address IP_port\n");
		exit(-1);
	}
	//1.创建套接字
	if((sfd=socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		perror("socket");
		exit(-1);
	}
	//2.connect()函数   链接服务器
	bzero(&sin,sizeof(sin));
	sin.sin_family=AF_INET;
	sin.sin_port=htons(atoi(argv[2]));

	if(inet_pton(AF_INET,argv[1],&sin.sin_addr.s_addr) != 1)
	{
		perror("inet_pton");
		exit(-1);
	}

	if(connect(sfd,(struct sockaddr*)&sin,sizeof(sin)) < 0)
	{
		perror("connect");
		exit(-1);
	}

	//3.读写数据
	fd_set rset;
	int maxfd=-1;
	struct timeval tout;
	char buf[64],serv_buf[64];
	while(1)
	{
		//清空集合
		FD_ZERO(&rset);
		//添加标准输入和套接字到集合
		FD_SET(0,&rset);
		FD_SET(sfd,&rset);
		//监听集合
		maxfd=sfd;
		tout.tv_sec = 5;
		tout.tv_usec = 0;
		if(select(maxfd+1,&rset,NULL,NULL,&tout) < 0)
		{
			perror("select");
			exit(-1);
		}
		//处理键盘输入数据
		if(FD_ISSET(0,&rset))
		{
			int ret=-1;
			bzero(buf,sizeof(buf));
			do{
				ret = read(0,buf,sizeof(buf)-1);
			}while(ret < 0 && EINTR==errno);
			if(ret < 0)
			{
				continue;
			}
			if(ret == 0)
			{
				break;
			}
			write(sfd,buf,strlen(buf));
			if(strcmp(buf,"quit\n") == 0)
			{
				printf("client exiting!\n");
				break;;
			}
		}

		//处理接收到服务器的数据
		if(FD_ISSET(sfd,&rset))
		{
			bzero(serv_buf,sizeof(serv_buf));
			read(sfd,serv_buf,sizeof(serv_buf));
			printf("from server massage:%s\n",serv_buf);
			if(strcmp(serv_buf,"quit\n") == 0)
			{
				printf("other client exiting!\n");
				continue;
			}
		}
	}

	//4.关闭fd
	close(sfd);
	return 0;
}
