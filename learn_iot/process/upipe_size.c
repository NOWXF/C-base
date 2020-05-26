#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int fpd[2];
	int count=0;
	char buf[1024];

	if(pipe(fpd) < 0)
	{
		perror("pipe failed");
		return -1;
	}

	while(1)
	{
		write(fpd[1],buf,1024);
		printf("total:%dk byte\n",++count);
	}

	return 0;
}
