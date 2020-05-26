#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

typedef struct{
	long type;
	char mtext[64];
}MSG;

#define LEN (sizeof(MSG)-sizeof(long))

int main()
{
	int msgid;
	key_t key;
	MSG buf;

	if((key=ftok(".",'q')) < 0)
	{
		perror("fotk failed");
		return -1;
	}

	if((msgid=msgget(key,IPC_CREAT|0666)) < 0)
	{
		perror("msg create failed");
		return -1;
	}

	while(1)
	{
		msgrcv(msgid,&buf,LEN,100,0);
		if(strcmp(buf.mtext,"quit\n") == 0)
		{
			msgctl(msgid,IPC_RMID,NULL);
			exit(0);
		}

		printf("receive:%s\n",buf.mtext);
		buf.type=200;
		fgets(buf.mtext,LEN,stdin);
		msgsnd(msgid,&buf,LEN,0);
		if(strcmp(buf.mtext,"quit\n") == 0) break;
	}

	return 0;
}
