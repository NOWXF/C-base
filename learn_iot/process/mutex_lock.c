#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define LOCK

int count=0,value1,value2;
pthread_mutex_t lock;

void *fun(void *args)
{
	while(1)
	{
#ifdef LOCK
		pthread_mutex_lock(&lock);
#endif
		if(value1 != value2)
			printf("v1:%d v2:%d\n",value1,value2);
		sleep(1);
#ifdef LOCK
		pthread_mutex_unlock(&lock);
#endif
	}
}

int main()
{
	int tid;
	pthread_t pth;

	if(pthread_mutex_init(&lock,NULL) != 0)
	{
		perror("mutex init failed");
		return -1;
	}

	if((tid=pthread_create(&pth,NULL,fun,NULL)) < 0)
	{
		perror("pthread create failed");
		return -1;
	}

	while(1)
	{
		count++;
#ifdef LOCK
		pthread_mutex_lock(&lock);
#endif
		value1=count;
		value2=count;
#ifdef LOCK
		pthread_mutex_unlock(&lock);
#endif
	}

	return 0;
}
