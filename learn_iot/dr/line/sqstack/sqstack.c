#include "sqstack.h"


sqstack * create_stack(int len)
{
	if(len <= 0)
	{
		puts("len < 0");
		return NULL;
	}
	sqstack *s;
	if((s=(sqstack *)malloc(sizeof(sqstack))) == NULL)
	{
		puts("malloc failed");
		return NULL;
	}
	if((s->data=(data_t *)malloc(sizeof(data_t)*len)) == NULL)
	{
		puts("malloc failed");
		return NULL;
	}
	s->maxlen=len;
	s->top=-1;
	return s;
}

void clear_stack(sqstack *s)
{
	if(s == NULL)
	{
		puts("stack is NULL");
		return ;
	}
	s->top=-1;
}

int is_empty_stack(sqstack *s)
{
	if(s == NULL)
	{
		puts("stack is NULL");
		return -1;
	}
	return (s->top == -1)?1:0;
}

int is_full_stack(sqstack *s)
{
	if(s == NULL)
	{
		puts("stack is NULL");
		return -1;
	}
	return (s->top == (s->maxlen-1))?1:0;
}

int push_stack(sqstack *s, data_t x)
{
	if(is_full_stack(s))
	{
		puts("stack is full");
		return -1;
	}
	s->data[++(s->top)]=x;
	return 1;
}

data_t pop_stack(sqstack *s)
{
	if(is_empty_stack(s))
	{
		puts("stack is empty");
		return 0;
	}
	return s->data[(s->top)--];
}

data_t get_top_stack(sqstack *s)
{
	if(is_empty_stack(s))
	{
		puts("stack is empty");
		return 0;
	}
	return s->data[s->top];	
}

void free_stack(sqstack *s)
{
	if(s == NULL)
	{
		puts("stack is NULL");
		return ;
	}
	free(s->data);
	s->data=NULL;
	free(s);
	s=NULL;
}
