#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define N 64

int main()
{
	char buf[N];
	int pfd;

	if((pfd=open("myfifo",O_RDONLY)) < 0)
	{
		perror("open myfifo failed");
		return -1;
	}
	printf("opne myfifo success!\n");

	while(read(pfd,buf,N) > 0)
	{
		printf("fifo characters:%d \n",strlen(buf));
	}

	close(pfd);
	return 0;
}
