#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	pid_t pid;
	FILE *fp;
	time_t t;

	if((pid=fork()) < 0)
	{
		perror("fork failed");
		return -1;
	}
	else if(pid > 0)
	{
		exit(-1);
	}

	setsid();
	chdir("/tmp");
	umask(0);
	int i;
	for(i=0;i<getdtablesize();i++)
	{
		close(i);
	}


	if((fp=fopen("time.log","a")) < 0)
	{
		exit(-1);
	}

	while(1)
	{
		time(&t);
		fprintf(fp,"%s\n",ctime(&t));
		fflush(fp);
		sleep(1);
	}
}
