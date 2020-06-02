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
#if 0
	struct sockaddr_un sun;
	bzero(&sun,sizeof(sun));
	if(access(SOCKET_NAME, F_OK|W_OK) != 0)
	{
		perror("access");
		exit(-1);
	}
	sun.sun_family=AF_UNIX;
	strncpy(sun.sun_path,SOCKET_NAME,sizeof(SOCKET_NAME));
	if(bind(fd,(struct sockaddr *)&sun,sizeof(sun)) < 0)
	{
		perror("bind");
		close(fd);
		exit(-1);
	}
#endif
	//connect连接服务器
	struct sockaddr_un cun;
	bzero(&cun,sizeof(cun));
	cun.sun_family=AF_UNIX;
	if(access(SOCKET_NAME, F_OK|W_OK) != 0)
	{
		perror("access");
		exit(-1);
	}
	strncpy(cun.sun_path,SOCKET_NAME,sizeof(SOCKET_NAME));
	if(connect(fd,(struct sockaddr *)&cun,sizeof(cun)) < 0)
	{
		perror("connect");
		exit(-1);
	}

	//数据收发及处理
	char buf[BUFFER_SIZE];
	int ret=-1;
	while(1)
	{
		bzero(buf,sizeof(buf));
		fgets(buf,sizeof(buf)-1,stdin);
		if(send(fd,buf,strlen(buf),0) < 0)
		{
			perror("send");
			exit(-1);
		}
		if( strcmp(buf,"quit\n") == 0)
		{
			printf("client quit\n");
			break;
		}


		bzero(buf,sizeof(buf));
		ret = recv(fd,buf,sizeof(buf)-1,0);
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

		printf("server msg:%s\n",buf);

	}

	//关闭套接字
	close(fd);
	return 0;
}
