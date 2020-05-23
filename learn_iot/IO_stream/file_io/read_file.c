#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,const char *argv[])
{
	int fd;
	int count=0,sum=0;
	char buf[64];

	if(argc < 2)
	{
		printf("usage:./count <file>\n");
		return -1;
	}

	if((fd=open(argv[1],O_RDONLY)) == -1)
	{
		perror("open failed");
		return -1;
	}

	while((count=read(fd,buf,sizeof(buf))) > 0)
	{
		sum+=count;
	}
	printf("total:%d\n",sum);
	
	close(fd);
	return 0;
}

