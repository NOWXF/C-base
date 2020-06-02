#include "net.h"

int main()
{
	int sfd;
	//1.创建socket套接字
	if((sfd=socket(AF_INET,SOCK_DGRAM,0)) < 0)
	{
		perror("socket");
		exit(-1);
	}
	//允许地址重用
	int b_reuse=-1;
	setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&b_reuse,sizeof(int));

	//设置并允许组播
	struct ip_mreq mreq;
	bzero(&mreq,sizeof(mreq));
	mreq.imr_multiaddr.s_addr=inet_addr(SOCK_ADDR);
	mreq.imr_interface.s_addr=htonl(INADDR_ANY);

	if(setsockopt(sfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0)
	{
		perror("GROUP");
		exit(-1);
	}

	//2.绑定
	struct sockaddr_in sin;
	bzero(&sin,sizeof(sin));
	sin.sin_family=AF_INET;
	sin.sin_port=htons(SOCK_PORT);
#if 1
	sin.sin_addr.s_addr=htonl(INADDR_ANY);
#else
	if(inet_pton(AF_INET,SOCK_ADDR,&sin.sin_addr.s_addr) < 0)
	{
		perror("inet_potn");
		exit(-1);
	}
#endif
	if(bind(sfd,(struct sockaddr *)&sin,sizeof(sin)) < 0)
	{
		perror("bind");
		exit(-1);
	}

	//3.阻塞等待接收数据
	char buf[64];
	struct sockaddr_in cin;
	socklen_t len=sizeof(cin);
	printf("boardcast receiver start OK!\n");
	while(1)
	{
		bzero(buf,sizeof(buf));
		bzero(&cin,sizeof(cin));
		//printf("buf sizeof:%d\n",sizeof(buf));
		if(recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr *)&cin,&len) < 0)
		{
			perror("recvfrom");
			exit(-1);
		}
		printf("buf recv:%ld\n",strlen(buf));
		//3.1处理接收的数据
		char ipv4_addr[16];
		if(inet_ntop(AF_INET,&cin.sin_addr.s_addr,ipv4_addr,sizeof(ipv4_addr)-1) < 0)
		{
			perror("inet_ntop");
			exit(-1);
		}
		//printf("buf size:%d\n",strlen(buf));
		printf("client(%s:%d):%s\n",ipv4_addr,ntohs(cin.sin_port),buf);
		if(strcmp(buf,"quit\n") == 0)
		{
			printf("client(%s:%d) quit!\n",ipv4_addr,ntohs(cin.sin_port));
			continue;
		}
		/*
		//4.发送返回数据
		char buf_ret[10]="over";
		cin.sin_family=AF_INET;
		cin.sin_port=SOCK_PORT;
		if(inet_pton(AF_INET,SOCK_ADDR,&cin.sin_addr.s_addr) < 0)
		{
			perror("inet_potn");
			exit(-1);
		}
		if(sendto(sfd,(void *)buf_ret,strlen(buf_ret),0,(struct sockaddr *)&cin,sizeof(cin)) < 0)
		{
			perror("sendto");
			exit(-1);
		}
		*/
	}

	//关闭
	close(sfd);
	return 0;
}
