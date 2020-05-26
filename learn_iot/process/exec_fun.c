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
		if(execl("/bin/ls","ls","-a","-l","/etc",NULL) < 0)
		{
			perror("execl failed");
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
