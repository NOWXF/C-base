#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"


dlinklist create_dlist(void)
{
	dlinklist H;
	if((H=(dlinklist)malloc(sizeof(dlistnode))) == NULL)
	{
		puts("malloc failed");
		return NULL;
	}
	H->next=H;
	H->prior=H;
	return H;
}

void show_dlist(dlinklist H)
{
	dlinklist temp;
	temp=H->next;
	while(temp != H)
	{
		printf("data=%d\n",temp->data);
		temp=temp->next;
	}
}

int insert_dlist(dlinklist H, data_t x, int pos)
{
	dlinklist d,p;
	if((d=(dlinklist)malloc(sizeof(dlistnode))) == NULL)
	{
		puts("malloc failed");
		return -1;
	}
	d->data=x;
	int i=0;
	p=H->next;
	while((p != H) && (i<pos))
	{
		p=p->next;
		i++;
	}
	if(i==pos)
	{
		d->prior=p->prior;
		d->next=p;
		p->prior->next=d;
		p->prior=d;
		puts("insert success");
		return 1;
	}
	else
	{
		puts("pos is invalid");
		return -1;
	}
}

dlinklist get_dlist(dlinklist H, int pos)
{
	dlinklist p;
	int i=0;
	p=H->next;
	while((i<pos) && (p!=H))
	{
		p=p->next;
		i++;
	}
	if(i == pos)
	{
		return p;
	}else{
		puts("pos is invalid");
		return NULL;
	}
}

int delete_dlist(dlinklist H, int pos)
{
	dlinklist del;
	int i=0;
	del=H->next;
	while((i<pos) && (del!=H))
	{
		del=del->next;
		i++;
	}
	if(i == pos)
	{
		del->prior->next=del->next;
		del->next->prior=del->prior;
		free(del);
		del=NULL;
		return 1;
	}else{
		puts("pos is invalid");
		return -1;
	}
}	
