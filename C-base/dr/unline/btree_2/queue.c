#include "queue.h"


que_pnode create_queue(void)
{
	que_pnode que;
	queue_pnode q;
	if((que=(que_pnode)malloc(sizeof(que_node))) == NULL)
	{
		puts("malloc failed");
		return NULL;
	}
	if((q=(queue_pnode)malloc(sizeof(queue_node))) == NULL)
	{
		puts("malloc failed");
		free(que);
		que=NULL;
		return NULL;
	}
	q->next=NULL;
	que->front=q;
	que->rear=q;
	return que;
}

int is_empty_queue(que_pnode q)
{
	if(q == NULL)
	{
		puts("queue is NULL");
		return -1;
	}
	if(q->front == q->rear)
	{
		puts("queue is empty");
		return 1;
	}
	else
		return 0;
}

int in_queue(que_pnode q, que_t value)
{
	queue_pnode d;
	if((d=(queue_pnode)malloc(sizeof(queue_node))) == NULL)
	{
		puts("malloc failed");
		return -1;
	}
	d->data=value;
	d->next=q->rear->next;
	q->rear->next=d;
	q->rear=d;
	return 1;
}

que_t out_queue(que_pnode q)
{
	if(is_empty_queue(q))
	{
		return NULL;
	}
	queue_pnode temp;
	temp=q->front;
	q->front=q->front->next;
	free(temp);
	temp=NULL;
	return q->front->data;
}

