#include "linkqueue.h"


queuelink create_queue(void)
{
	linkqueue_p Q;
	queuelink QL;
	if((Q=(linkqueue_p)malloc(sizeof(linkqueue_node))) == NULL)
	{
		puts("malloc failed");
		return NULL;
	}
	if((QL=(queuelink)malloc(sizeof(queuenode))) == NULL)
	{
		puts("malloc failed");
		return NULL;
	}
	Q->next = NULL;
	QL->front=Q;
	QL->rear=Q;
	return QL;
}

void clear_queue(queuelink Q)
{
	if(Q == NULL || Q->front == NULL)
	{
		puts("Queue is NULL");
		return ;
	}
	linkqueue_p temp;
	temp = 	Q->front;
	while(temp != NULL)
	{
		Q->front = Q->front->next;
		free(temp);
		temp=Q->front;
	}
	free(Q);
	Q=NULL;
}

void show_queue(queuelink Q)
{
	if(Q == NULL || Q->front == NULL)
	{
		puts("Queue is NULL");
		return ;
	}
	if(!is_empty_queue(Q))
	{
		linkqueue_p temp;
		temp = Q->front->next;
		printf("queue=");
		while(temp != NULL)
		{
			printf("%d ",temp->data);
			temp = temp->next;
		}
		printf("\n");
	}
}

int is_empty_queue(queuelink Q)
{
	if(Q == NULL || Q->front == NULL)
	{
		puts("Queue is NULL");
		return -1;
	}
	if(Q->front == Q->rear)
	{
		puts("Queue is empty");
		return 1;
	}
	else
	{
		return 0;
	}
}

int in_queue(queuelink Q, data_t value)
{
	if(Q == NULL || Q->front == NULL)
	{
		puts("Queue is NULL");
		return -1;
	}
	linkqueue_p d;
	if((d=(linkqueue_p)malloc(sizeof(linkqueue_node))) == NULL)
	{
		puts("malloc failed");
		return -1;
	}
	d->data=value;
	d->next=Q->rear->next;
	Q->rear->next=d;
	Q->rear=d;
	return 1;
}

data_t out_queue(queuelink Q)
{
	if(Q == NULL || Q->front == NULL)
	{
		puts("Queue is NULL");
		return -1;
	}
	if(!is_empty_queue(Q))
	{
#if 0
		linkqueue_p temp;
		temp=Q->front->next;
		if(Q->front->next == Q->rear)
		{
			Q->rear=Q->front;
		}
		Q->front->next=temp->next;
		data_t ret=temp->data;
		free(temp);
		temp=NULL;
		return ret;
#endif 
		linkqueue_p temp;
		temp=Q->front;
		Q->front=Q->front->next;
		free(temp);
		temp=NULL;
		return Q->front->data;
	}
	return -1;
}

