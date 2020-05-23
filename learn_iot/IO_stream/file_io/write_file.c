#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main(int argc,const char *argv[])
{
	int fd=0;
	char buf[64];

	if(argc < 2)
	{
		printf("usage:%s <file>\n",argv[0]);
		return -1;
	}
	if((fd=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0666)) < 0)
	{
		perror("open file");
		return -1;
	}

	while(gets(buf,sizeof(buf),stdin) != NULL)
	{
		if(strcmp(buf,"quit\n") == 0)
			break;
		write(fd, buf, strlen(buf));
	}
		
	close(fd);		
	return 0;
}
