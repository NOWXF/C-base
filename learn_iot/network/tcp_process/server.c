#include "net.h"

#define SOCK_ADDR "127.0.0.1"
#define SOCK_PORT 5001

void signal_handler(int signo)
{
	if(SIGCHLD == signo)
	{
		waitpid(-1,NULL,WNOHANG);
	}
}

int main()
{
	int sfp;
	struct sockaddr_in sin;
	//设置信号响应
	signal(SIGCHLD,signal_handler);
	//1.创建套接字
	if((sfp=socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		perror("socket");
		exit(-1);
	}
	//2.绑定
	//2.1填充sockaddr_in结构体
	bzero(&sin,sizeof(sin));
	sin.sin_family=AF_INET;
	sin.sin_port=htons(SOCK_PORT);
	//优化1：将服务器程序可以放在任意IP上
	sin.sin_addr.s_addr=htonl(INADDR_ANY);
	//2.2绑定
	if(bind(sfp,(struct sockaddr *)&sin,sizeof(sin)) < 0)
	{
		perror("bind");
		exit(-1);
	}
	//3.listen函数
	if(listen(sfp,5) < 0)
	{
		perror("listen");
		exit(-1);
	}
	//4.accept函数  阻塞等待客户端的链接
	int new_fd=-1;
	//优化2：获取来自客户端的信息
	struct sockaddr_in cin;
	socklen_t len;
	while(1)
	{
		if((new_fd=accept(sfp,(struct sockaddr *)&cin,&len)) < 0)
		{
			perror("accept");
			exit(-1);
		}
		else{
			//优化3：使用多进程接收客户端消息
			pid_t pid;
			if((pid=fork()) < 0)
			{
				perror("fork");
				exit(-1);
			}
			else if(pid == 0)
			{
				close(sfp);
				char ipv4_ip[16];
				if(inet_ntop(AF_INET,&cin.sin_addr.s_addr,ipv4_ip,len) == NULL)
				{
					perror("inet_ntop");
					exit(-1);
				}
				printf("%s:%d\n",ipv4_ip,ntohs(cin.sin_port));
				//5.读写数据
				char buf[64];
				int ret;
				while(1)
				{
					ret=-1;
					bzero(buf,sizeof(buf));
					do{
						ret = read(new_fd,buf,sizeof(buf)-1);
						printf("ret:%d\n",ret);
					}while(ret < 0 && EINTR == errno);
					printf("client(%s:%d):%s\n",ipv4_ip,ntohs(cin.sin_port),buf);
					if(strcmp(buf,"quit\n") == 0 || ret == 0)
						break;
				}

				close(new_fd);

				return 0;
			}
			else
			{
				close(new_fd);
			}
		}
	}
	// 6.关闭fd
	close(sfp);
	return 0;
}
