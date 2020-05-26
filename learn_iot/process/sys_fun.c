#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
	pid_t pid;
	if((pid=fork()) < 0)
	{
		perror("fork failed");
		return -1;
	}
	else if(pid == 0)
	{
		if(system("ls -l /home/x") < 0)
		{
			perror("system failed");
			exit(-1);
		}
	}
	else
	{
		printf("father pid:%d\n",getpid());
		sleep(1);
	}

	return 0;
}
