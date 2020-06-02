#include "net.h"

int main()
{
	int fd;
	//创建套接字
	if((fd=socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		perror("socket");
		exit(-1);
	}
	//设置地址重用
	int b_reuse=-1;
	setsockopt(fd,SOL_SOCKET,SO_RUSEADDR,&b_reuse,sizeof(int));
	//绑定IP和端口号
	struct sockaddr_in sin;
	sin.sin_family=AF_INET;
	sin.sin_port=htons(SOCK_PORT);
	if(inet_pton(AF_INET,SOCK_ADDR,&sin.sin_addr.s_addr) < 0)
	{
		perror("inet_pton");
		exit(-1);
	}
	//监听套接字
	if(listen(fd,0) < 0)
	{
		perror("listen");
		exit(-1);
	}
	fd_set rset;
	int max=-1;	
	char buf_recv[64];
	struct timeval tout;
	int new_fd;
	struct sockaddr cin;
	socklen_t len;
	while(1)
	{
		bzero(buf_recv,sizeof(buf_recv));
		max=fd;
		//清空集合
		FD_ZERO(&rset);	
		//添加fd到集合
		FD_SET(fd,&rset);
		//select()监控集合
		tout.tv_sec=5;
		tout.tv_usec=0;
		if(select(max+1,&rset,NULL,NULL,&tout) < 0)
		{
			perror("select");
			exit(-1);
		}
		//响应判断
		if(FD_ISSET(fd,&rset))
		{
			len=sizeof(cin);
			if((new_fd = accept(fd,(struct sockaddr *)&cin,&len)) < 0)
			{
				perror("accept");
				exit(-1);
			}
		}
	}

	close(fd);
	return 0;
}
