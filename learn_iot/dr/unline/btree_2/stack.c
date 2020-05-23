#include "stack.h"


void create_stack(stack_pnode *s)
{
	stack_pnode stack;
	if((stack=(stack_pnode)malloc(sizeof(stack_node))) == NULL)
	{
		puts("malloc failed");
		*s = NULL;
		return ;
	}
	stack->next=NULL;
	*s=stack;
}
	
int is_empty_stack(stack_pnode s)
{
	if(NULL==s->next)
	{
		puts("stack is empty");
		return 1;
	}
	else{
		return 0;
	}
}

int push_stack(stack_pnode s, stack_t value)
{
	stack_pnode temp;
	if((temp=(stack_pnode)malloc(sizeof(stack_node))) == NULL)
	{
		puts("malloc failed");
		return -1;
	}
	temp->data=value;
	temp->next=s->next;
	s->next=temp;
	return 1;
}

stack_t pop_stack(stack_pnode s)
{
	if(!is_empty_stack(s))
	{
		stack_pnode temp;
		temp=s->next;
		s->next=temp->next;
		stack_t ret;
		ret=temp->data;
		free(temp);
		temp=NULL;
		return ret;
	}
	return NULL;
	//exit(2);
}

stack_t get_top_stack(stack_pnode s)
{
	if(!is_empty_stack(s))
	{
		stack_t ret;
		ret = s->next->data;
		return ret;
	}
	return NULL;
	//exit(2);
}
