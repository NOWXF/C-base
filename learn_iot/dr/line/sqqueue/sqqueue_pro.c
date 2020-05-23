#include "sqqueue.h"


queuelink create_queue()
{
	queuelink q;
	if((q=(queuelink)malloc(sizeof(queuenode))) == NULL)
	{
		puts("malloc is failed");
		return NULL;
	}
	q->front=MAXSIZE-1;
	q->rear=MAXSIZE-1;
	return q;
}

void clear_queue(queuelink Q)
{
	if(Q == NULL)
	{
		puts("Queue is NULL");
		return;
	}
	free(Q);
	Q=NULL;
}

void show_queue(queuelink Q)
{
	if(Q == NULL)
	{
		puts("Queue is NULL");
		return;
	}
	if(is_empty_queue(Q))
	{
		puts("Queue is empty");
		return;
	}
	int front,rear;
	front=Q->front;
	rear=Q->rear;
	printf("queue:");
	while(rear!=front)
	{
		front=(front+1)%MAXSIZE;
		printf("%d ",Q->data[front]);
	}
	printf("\n");
}

int is_empty_queue(queuelink Q)
{
	if(Q == NULL)
	{
		puts("Queue is NULL");
		return -1;
	}
	if(Q->front == Q->rear)
	{
		puts("Queue is empty");
		return 1;
	}
	return 0;
}

int is_full_queue(queuelink Q)
{
	if(Q == NULL)
	{
		puts("Queue is NULL");
		return -1;
	}
	int rear=Q->rear;
	rear=(rear+1)%MAXSIZE;
	if(rear == Q->front)
	{
		puts("Queue is full");
		return 1;
	}
	return 0;
}

int in_queue(queuelink Q, data_t value)
{
	if(Q == NULL)
	{
		puts("Queue is NULL");
		return -1;
	}
	if(!is_full_queue(Q))
	{
		int rear=Q->rear;
		rear=(rear+1)%MAXSIZE;
		Q->data[rear]=value;
		Q->rear=rear;
		return 1;
	}
	return 0;
}
data_t out_queue(queuelink Q)
{
	if(Q == NULL)
	{
		puts("Queue is NULL");
		return -1;
	}
	if(!is_empty_queue(Q))
	{
		Q->front=(Q->front+1)%MAXSIZE;
		return Q->data[Q->front];
	}
	return -1;
}
