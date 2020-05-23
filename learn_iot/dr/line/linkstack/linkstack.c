#include "linkstack.h"


linkstack create_stack(void)
{
	linkstack s;
	if((s=(linkstack)malloc(sizeof(stacknode))) == NULL)
	{
		puts("malloc is failed");
		return NULL;
	}
	s->next=NULL;
	return s;
}

void clear_stack(linkstack s)
{
	if(s == NULL)
	{
		puts("statck is NULL");
		return ;
	}
	linkstack temp=s;
	while(temp != NULL)
	{
		s=s->next;
		free(temp);	
		temp=s;
	}
}

int is_empty_stack(linkstack s)
{
	if(s == NULL)
	{
		puts("stack is NULL");
		return -1;
	}
	return (s->next == NULL)?1:0;
}

#if 0
int is_full_stack(linkstack s)
{
	if(s == NULL)
	{
		puts("stack is NULL");
		return -1;
	}
	
}
#endif

int push_stack(linkstack s, data_t value)
{
	if(s == NULL)
	{
		puts("stack is NULL");
		return -1;
	}
	linkstack d;
	if((d=(linkstack)malloc(sizeof(stacknode))) == NULL)
	{
		puts("malloc is failed");
		return -1;
	}
	d->data=value;
	d->next=s->next;
	s->next=d;
	return 1;
}

data_t pop_stack(linkstack s)
{
	if(s == NULL)
	{
		puts("stack is NULL");
		return -1;
	}
	if(is_empty_stack(s))
		return -1;
	linkstack temp;
	data_t d;
	temp=s->next;
	s->next=temp->next;
	
	d=temp->data;
	free(temp);
	temp=NULL;
	return d; 
}

data_t get_top_stack(linkstack s)
{
	if(s == NULL)
	{
		puts("stack is NULL");
		return -1;
	}
	if(is_empty_stack(s))
		return -1;
	return s->next->data;
}

