#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int main()
{
	alarm(3);
	pause();
	printf("I have been awake!\n");
	return 0;
}
