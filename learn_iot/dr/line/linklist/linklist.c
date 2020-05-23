#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

linklist creat_linklist(void)
{
	linklist H;
	H = (linklist)malloc(sizeof(listnode));
	if(H == NULL)
	{
		puts("malloc failed");
		return H;
	}
	H->data=0;
	H->next=NULL;
	return H;
}

linklist creat1_linklist(void)
{
	linklist H,r;
	H = (linklist)malloc(sizeof(listnode));
	if(H == NULL)
	{
		puts("malloc failed");
		return H;
	}
	H->data=0;
	H->next=NULL;
	r=H;
	data_t data;
	while(1){
		printf("input a data:");
		scanf("%d",&data);
		if(data == -1)
		{
			break;
		}
		linklist p;
		if((p=(linklist)malloc(sizeof(listnode))) == NULL)
		{
			puts("malloc failed");
			break;
		}
		r->next=p;
		p->data=data;
		p->next=NULL;
		r=p;
	}
	return H;
}

void clear_linklist(linklist L)
{
	if(L == NULL)
	{
		puts("linklist is NULL");
		return ;
	}
	linklist temp;
	while(L)
	{
		temp=L->next;
		free(L);
		L=temp;
	}
	L=NULL;
	temp=NULL;
	return ;
}

void show_linklist(linklist L)
{
	if(L == NULL)
	{
		puts("linklist is NULL");
		return ;
	}
	L=L->next;
	while(L != NULL)
	{
		printf("data=%d\n",L->data);
		L = L->next;
	}
}




int insert_linklist(linklist L, data_t x, int pos)
{
	linklist temp=L->next;
	if(L == NULL)
	{
		puts("linklist is NULL");
		return -1;
	}
	if(pos < 1)
	{
		puts("pos is invalid");
		return -1;
	}
	int i=1;
	while((pos != i)&&(temp != NULL))
	{
		L=temp;
		temp=temp->next;
		i++;
	}
	if(pos == i)
	{
		linklist d;
		if((d=(linklist)malloc(sizeof(listnode))) == NULL)
		{
			puts("insert malloc failed");
			return -1;
		}
		d->data=x;
		d->next=L->next;
		L->next=d;
		return 1;
	}else{
		return -1;
	}
	return 1;
}

int order_insert_linklist(linklist L, data_t x)
{
	linklist p,q;
	if((p=(linklist)malloc(sizeof(listnode))) == NULL){
		puts("malloc failed");
		return -1;
	}
	p->data=x;
	q=L;
	while(q->next && q->next->data < x)
	{
		q=q->next;
	}

	p->next=q->next;
	q->next=p;
	return 1;
}

linklist get_by_pos_linklist(linklist L, int pos){
	linklist temp=L->next;
	if(L == NULL)
	{
		puts("linklist is NULL");
		return NULL;
	}
	if(pos < 0)
	{
		puts("pos is invalid");
		return NULL;
	}
	int i=0;
	while(temp!=NULL)
	{
		if(i == pos)
			break;
		temp=temp->next;
		i++;
	}
	if(i == pos)
		return temp;
	else
	{
		printf("pos is invalid");
		return NULL;
	}
}

linklist get_by_data_linklist(linklist L, data_t x){
	linklist temp=L->next;
	if(L == NULL)
	{
		puts("linklist is NULL");
		return NULL;
	}
	while(temp != NULL)
	{
		if(temp->data == x)
			break;
		temp=temp->next;
	}
	if(temp != NULL)
		return temp;
	else
	{
		puts("data is not found");
		return NULL;
	}
}


int delete_by_pos_linklist(linklist L, int pos)
{
	linklist temp,del;
	if(L == NULL)
	{
		puts("linklist is NULL");
		return -1;
	}
	if(pos == 0)
		temp = L;
	else
		temp = get_by_pos_linklist(L, pos-1);
	if(temp && temp->next){
		del=temp->next;
		temp->next=del->next;
		free(del);
		del=NULL;
		puts("delete success");
		return 1;
	}else{
		puts("pos is invalid");
		return - 1;
	}
}

int delete_by_data_linklist(linklist L, data_t x)
{
	linklist temp,del;
	if(L == NULL)
	{
		puts("linklist is NULL");
		return -1;
	}
	temp=L;
	while(temp->next){
		if(temp->next->data == x)
			break;
		temp = temp->next;
	}
	if(temp->next != NULL)
	{
		del = temp->next;
		temp->next = del->next;
		free(del);
		del=NULL;
		puts("delete success");
		return 1;
	}else{
		puts("value is not found");
		return -1;
	}
}

linklist reverse_linklist(linklist L)
{
	linklist R;
	R = creat_linklist();
	if( R == NULL){
		puts("new linklist create failed");
		return NULL;
	}
	while(L->next!=NULL)
	{
		insert_linklist(R, L->next->data, 1);
		L = L->next;
	}
	return R;
}
void self_reverse_linklist(linklist L)
{
	linklist p,q;
	p=L->next;
	L->next=NULL;
	while(p){
		q=p;
		p=q->next;
		q->next=L->next;
		L->next=q;
	}
}

void sort_linklist(linklist L)
{
	linklist p,q,r;
	p=L->next;
	L->next=NULL;
	while(p){
		q=p;
		p=p->next;
		r=L;
		while(r->next && r->next->data < q->data)
		{
			r=r->next;
		}
		q->next=r->next;
		r->next=q;
	}
}

void join_linklist(linklist L, linklist K)
{
	linklist p,q;
	while(K->next){
		p=L;
		if((q=(linklist)malloc(sizeof(listnode))) == NULL)
		{
			puts("malloc failed");
			return ;
		}
		K=K->next;
		q->data=K->data;
		while(p->next && p->next->data < q->data)
		{
			p=p->next;
		}
		q->next=p->next;
		p->next=q;
	}
}
