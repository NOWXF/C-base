#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define N 64

int main()
{
	char buf[N];
	int pfd;

	if((pfd=open("myfifo",O_WRONLY)) < 0)
	{
		perror("open myfifo failed");
		return -1;
	}
	printf("opne myfifo success!\n");

	while(1)
	{
		fgets(buf,N,stdin);
		if(strcmp(buf,"quit\n") == 0)
			break;
		write(pfd,buf,N);
	}
	close(pfd);
	return 0;
}
