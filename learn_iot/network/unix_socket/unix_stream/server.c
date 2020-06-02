#include "net.h"

int main()
{
	int fd;
	//创建unix域流式套接字
	if((fd=socket(AF_UNIX,SOCK_STREAM,0)) < 0)
	{
		perror("socket");
		exit(-1);
	}
	//绑定本地地址
	struct sockaddr_un sun;
	if(access(SOCKET_NAME,F_OK) == 0)
	{
		unlink(SOCKET_NAME);
	}
	sun.sun_family=AF_UNIX;
	strncpy(sun.sun_path,SOCKET_NAME,sizeof(SOCKET_NAME));
	if(bind(fd,(struct sockaddr *)&sun,sizeof(sun)) < 0)
	{
		perror("bind");
		close(fd);
		exit(-1);
	}
	//监听
	if(listen(fd,5) < 0)
	{
		perror("listen");
		exit(-1);
	}
	//accept等待建立连接
	int data_fd;
	if((data_fd=accept(fd,NULL,NULL)) < 0)
	{
		perror("accept");
		exit(-1);
	}

	//数据收发及处理
	char buf[BUFFER_SIZE];
	int ret=-1;
	while(1)
	{
		bzero(buf,sizeof(buf));
		ret = recv(data_fd,buf,sizeof(buf)-1,0);
		if(ret  < 0)
		{
			perror("recv");
			exit(-1);
		}
		if(ret == 0)
		{
			printf("client is exiting!\n");
			break;
		}

		printf("client msg:%s\n",buf);
		if( strcmp(buf,"quit\n") == 0)
		{
			printf("client quit\n");
			break;
		}

		bzero(buf,sizeof(buf));
		strcpy(buf,"server receive data");
		if(send(data_fd,buf,sizeof(buf),0) < 0)
		{
			perror("send");
			exit(-1);
		}
	}

	//关闭套接字
	close(fd);
	return 0;
}
