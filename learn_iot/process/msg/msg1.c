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
		buf.type=100;
		fgets(buf.mtext,LEN,stdin);
		msgsnd(msgid,&buf,LEN,0);
		if(strcmp(buf.mtext,"quit\n") == 0) break;
		msgrcv(msgid,&buf,LEN,200,0);
		if(strcmp(buf.mtext,"quit\n") == 0)
		{
			msgctl(msgid,IPC_RMID,NULL);
			exit(0);
		}

		printf("receive:%s\n",buf.mtext);

	}

	return 0;
}
