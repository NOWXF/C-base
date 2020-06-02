#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

char memery[30]="hello world!";

void *fun(void *arg)
{
	strcpy(memery,"pthread massage");
	pthread_exit("thank you for waiting for me");
}

int main()
{
	pthread_t *pth;
	char *ret;
	int tid;

	if((tid=pthread_create(pth,NULL,fun,NULL)) != 0)
	{
		perror("thread create failed");
		return -1;
	}

	pthread_join(*pth,(void**)&ret);
	printf("ret:%s\n",ret);
	printf("memery:%s\n",memery);
	return 0;
}

