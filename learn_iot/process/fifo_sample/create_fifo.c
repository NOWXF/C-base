#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	if(mkfifo("myfifo",0666) < 0)
	{
		perror("fifo create failed");
		return -1;
	}
	printf("create fifo success!\n");
	return 0;
}
