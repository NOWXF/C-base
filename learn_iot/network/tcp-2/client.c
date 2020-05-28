#include "net.h"

#define SOCK_ADDR "127.0.0.1"
#define SOCK_PORT 5001

int main()
{
	int sfd;
	struct sockaddr_in sin;
	//1.创建套接字
	if((sfd=socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		perror("socket");
		exit(-1);
	}
	//2.connect()函数   链接服务器
	bzero(&sin,sizeof(sin));
	sin.sin_family=AF_INET;
	sin.sin_port=htons(SOCK_PORT);
#if 0
	sin.sin_addr.s_addr=inet_addr(SOCK_ADDR);
#else

	if(inet_pton(AF_INET,SOCK_ADDR,&sin.sin_addr.s_addr) != 1)
	{
		perror("inet_pton");
		exit(-1);
	}
#endif

	if(connect(sfd,(struct sockaddr*)&sin,sizeof(sin)) < 0)
	{
		perror("connect");
		exit(-1);
	}
	//5.读写数据
	char buf[64];
	while(1)
	{
		bzero(buf,sizeof(buf));
		fgets(buf,sizeof(buf)-1,stdin);
		write(sfd,buf,strlen(buf));
		if(strcmp(buf,"quit\n") == 0)
			break;
	}

	//4.关闭fd
	close(sfd);
	return 0;
}
