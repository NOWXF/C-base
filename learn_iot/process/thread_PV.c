#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include <pthread.h>

char buf[64];
sem_t  sem;

void *fun(void *args)
{
	while(1)
	{
		sem_wait(&sem);
		printf("\nbuf size:%ld character\n",strlen(buf));
	}
}


int main()
{
	int tid;
	pthread_t pth;

	if(sem_init(&sem,0,0) < 0)
	{
		perror("sem init failed");
		return -1;
	}

	if((tid=pthread_create(&pth,NULL,fun,NULL)) < 0)
	{
		perror("pthread create failed");
		return -1;
	}
	
	do{
		printf("input:");
		fgets(buf,64,stdin);
		sem_post(&sem);
	}while(strncmp(buf,"quit",4) != 0);

	return 0;
}

