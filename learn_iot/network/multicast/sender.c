#include "net.h"

int main(int argc,char **argv)
{
	int sfd;

	if(argc < 3)
	{
		printf("usage:./client serv_ip serv_port\n");
		exit(-1);
	}
	//1.创建socket套接字
	if((sfd=socket(AF_INET,SOCK_DGRAM,0)) < 0)
	{
		perror("socket");
		exit(-1);
	}

	//2.发送数据包给服务器
	char buf_snd[64];
	struct sockaddr_in sin;
	bzero(&sin,sizeof(sin));
	sin.sin_family=AF_INET;
	sin.sin_port=htons(atoi(argv[2]));
#if 0
	sin.sin_addr.s_addr=htosl(ADDRANY);
#else
	if(inet_pton(AF_INET,argv[1],&sin.sin_addr.s_addr) < 0)
	{
		perror("inet_pton");
		exit(-1);
	}
#endif
	while(1)
	{
		bzero(buf_snd,sizeof(buf_snd));
		//接收来自输入数据
		if(fgets(buf_snd,sizeof(buf_snd),stdin) == NULL)
		{
			continue;
		}
		if(sendto(sfd,(void *)buf_snd,strlen(buf_snd),0,(struct sockaddr *)&sin,sizeof(sin)) < 0)
		{
			perror("sendto");
			exit(-1);
		}
		if(strcmp(buf_snd,"quit\n") == 0)
		{
			printf("client quit\n");
			break;
		}

		/*
		//3.接收来自服务器反馈数据
		char buf_ret[64];
		struct sockaddr_in cin;
		socklen_t len=sizeof(cin);
		bzero(&cin,sizeof(cin));
		if(recvfrom(sfd,(void *)buf_ret,sizeof(buf_ret)-1,0,(struct sockaddr *)&cin,&len) < 0)
		{
		perror("recvfrom");
		exit(-1);
		}
		//3.1处理接收的数据
		char ipv4_addr[16];
		if(inet_ntop(AF_INET,&cin.sin_addr.s_addr,ipv4_addr,sizeof(ipv4_addr)-1) < 0)
		{
		perror("inet_ntop");
		exit(-1);
		}
		printf("server(%s:%d):%s",ipv4_addr,ntohs(cin.sin_port),buf_ret);

*/
	}
	//关闭
	close(sfd);
	return 0;
}
