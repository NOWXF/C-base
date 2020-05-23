#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc,const char *argv[])
{
	int fs,fd,n;
	char buf[64];

	if(argc < 3)
	{
		printf("usage:%s <file1> <file2>\n",argv[0]);
		return -1;
	}

	if((fs=open(argv[1],O_RDONLY)) < 0)
	{
		perror("open src file");
		return -1;
	}
	if((fd=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0666)) < 0)
	{
		perror("open dest file");
		return -1;
	}

	while((n = read(fs,buf,sizeof(buf))) > 0)
	{
		write(fd,buf,n);
	}

	close(fs);
	close(fd);
	return 0;
}
