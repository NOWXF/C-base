#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void *handler(int signo)
{
	if(SIGINT == signo)
		printf("I got signal SIGINT.\n");
	if(SIGQUIT == signo)
		printf("I got signal SIGQUIT.\n");
}

int main()
{
	signal(SIGINT,handler);
	signal(SIGQUIT,handler);
	while(1)pause();
	return 0;
}
