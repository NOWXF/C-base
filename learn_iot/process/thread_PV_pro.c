#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include <pthread.h>

char buf[64];
sem_t  sem_r,sem_w;

void *fun(void *args)
{
	while(1)
	{
		sem_wait(&sem_r);
		printf("buf size:%ld character\n",strlen(buf));
		sem_post(&sem_w);
	}
}


int main()
{
	int tid;
	pthread_t pth;

	if(sem_init(&sem_r,0,0) < 0)
	{
		perror("sem_r init failed");
		return -1;
	}
	if(sem_init(&sem_w,0,1) < 0)
	{
		perror("sem_w init failed");
		return -1;
	}

	if((tid=pthread_create(&pth,NULL,fun,NULL)) < 0)
	{
		perror("pthread create failed");
		return -1;
	}
	
	do{
		sem_wait(&sem_w);
		printf("input:");
		fgets(buf,64,stdin);
		sem_post(&sem_r);
	}while(strncmp(buf,"quit",4) != 0);

	return 0;
}

