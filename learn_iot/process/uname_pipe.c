#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	pid_t pid1,pid2;
	char buf[64];
	int pfd[2];

	if(pipe(pfd) < 0)
	{
		perror("pipe create failed");
		return -1;
	}

	if((pid1=fork()) < 0)
	{
		perror("fork failed");
		return -1;
	}
	else if(pid1 == 0)
	{
		strcpy(buf,"process pid1");
		write(pfd[1],buf,64);
		exit(0);
	}
	else{
		if((pid2=fork()) < 0)
		{
			perror("fork2 failed");
			exit(-1);
		}
		else if(0 == pid2)
		{
			sleep(1);
			strcpy(buf,"process pid2");
			write(pfd[1],buf,64);
			exit(0);
		}
		else{
			wait(NULL);
			read(pfd[0],buf,64);
			printf("%s\n",buf);

			wait(NULL);
			read(pfd[0],buf,64);
			printf("%s\n",buf);
		}
	}

	return 0;
}
