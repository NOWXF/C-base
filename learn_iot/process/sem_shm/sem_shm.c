#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>
#include <signal.h>

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};

int main()
{
	pid_t pid;
	key_t key;
	int shmid;
	int semid;
	char * buf;
	struct sembuf s_buf[2];
	union semun mysem;

	//获取key
	if((key=ftok(".",'a')) < 0)
	{
		perror("ftok");
		return -1;
	}

	//创建共享内存
	if((shmid=shmget(key,64,IPC_CREAT|0666)) < 0)
	{
		perror("shmget");
		return -1;
	}

	//获取共享内存地址
	if((buf=(char *)shmat(shmid,NULL,0)) == (void *)-1)
	{
		perror("shmat");
		return -1;
	}

	//创建信号灯集
	if((semid=semget(key,2,IPC_CREAT|0666)) < 0)
	{
		perror("semget");
	}
	else{
		//初始化信号灯集
		mysem.val=0;
		if(semctl(semid,0,SETVAL,mysem) < 0)
		{
			perror("semctl");
			exit(-1);
		}
		mysem.val=1;
		if(semctl(semid,1,SETVAL,mysem) < 0)
		{
			perror("semctl1");
			exit(-1);
		}
	}

	//创建多线程
	if((pid=fork()) < 0)
	{
		perror("fork");
		return -1;
	}
	else if(0 == pid)
	{
		while(1)
		{
		//对读数据进行P操作	
		s_buf[0].sem_num=0;
		s_buf[0].sem_op=-1;
		s_buf[0].sem_flg=0;

		semop(semid,s_buf,1);

		//读取数据并删除空格
		for(int i=0;i<64;i++)
		{
			if(buf[i] != ' ')
				printf("%c",buf[i]);
		}

		//对写数据进行V操作
		s_buf[0].sem_num=1;
		s_buf[0].sem_op=1;
		s_buf[0].sem_flg=0;
		semop(semid,s_buf,1);
		}
	}
	else{
	while(1)
	{
		//对写数据进行P操作	
		s_buf[0].sem_num=1;
		s_buf[0].sem_op=-1;
		s_buf[0].sem_flg=0;

		semop(semid,s_buf,1);

		//读取键盘输入写入共享内存
		fgets(buf,64,stdin);
		if(strcmp(buf,"quit\n") == 0)
		{
			//删除信号灯 
			semctl(semid,0,IPC_RMID);
			semctl(semid,1,IPC_RMID);
			//删除共享内存
			shmdt(buf);
			shmctl(shmid,IPC_RMID,NULL);
			kill(pid,SIGUSR1);
			break;
		}

		//对读数据进行V操作
		s_buf[0].sem_num=0;
		s_buf[0].sem_op=1;
		s_buf[0].sem_flg=0;
		semop(semid,s_buf,1);
	}
	}

	return 0;
}
