#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	pid_t pid;

	if((pid=fork()) < 0)
	{
		perror("fork failed");
		return 0;
	}
	else if(pid == 0)
	{
		printf("child pid:%d\n",getpid());
		exit(0);
	}
	else
	{
		printf("father pid:%d\n",getpid());
		sleep(1);
	}
	return 0;
}
