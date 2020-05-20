#include <stdio.h>
#include <stdlib.h>
#include "seqlist.h"

seqlist *creat_seqlist(void)
{
	seqlist *L=NULL;
	L=(seqlist *)malloc(sizeof(seqlist));
	if(L==NULL)
	{
		puts("momery is null");
		return NULL;
	}
	L->last=-1;
	return L;
}

void clear_seqlist(seqlist *L)
{
	if(L==NULL)
	{
		puts("seqlist is NULL");
		return ;
	}
	free(L);
	L=NULL;
}



int is_empty_seqlist(seqlist *L)
{
	if(L==NULL)
	{
		puts("seqlist is NULL");
		return -1;
	}
	return (L->last == -1);
}
	
int is_full_seqlist(seqlist *L)
{
	if(L==NULL)
	{
		puts("seqlist is NULL");
		return -1;
	}
	return (L->last == MAXSIZE-1);
}

void set_empty_seqlist(seqlist *L)
{
	if(L==NULL)
	{
		puts("seqlist is NULL");
		return ;
	}
	L->last=-1;
}
	
int get_length_seqlist(seqlist *L)
{
	if(L==NULL)
	{
		puts("seqlist is NULL");
		return -1;
	}
	return L->last+1;
}
	
void show_seqlist(seqlist *L)
{
	if(L==NULL)
	{
		puts("seqlist is NULL");
		return ;
	}
	for(int i=0;i<=L->last;i++)
	{
		printf("L->data[%d]=%d\n",i, L->data[i]);
	}
}



int insert_seqlist(seqlist *L, data_t x, int pos)
{
	int i=0;
	if(is_full_seqlist(L)||pos<0||pos>MAXSIZE-1)
	{
		puts("insert failed");
		return -1;
	}
	for(i=L->last;i>=pos;i--)
	{
		L->data[i+1]=L->data[i];
	}
	L->data[pos]=x;
	L->last++;
	return 1;
}

int delete_seqlist(seqlist *L, int pos)
{
	if(L==NULL)
	{
		puts("seqlist is NULL");
		return -1;
	}
	if(is_empty_seqlist(L)||pos<0||pos>(L->last))
	{
		puts("delete failed");
		return -1;
	}
	for(int i=pos;i<L->last;i++)
	{
		L->data[i]=L->data[i+1];
	}
	L->last--;
	return 1;
}
	
int change_seqlist(seqlist *L, data_t x, int pos)
{
	if(L==NULL)
	{
		puts("seqlist is NULL");
		return -1;
	}
	if(is_empty_seqlist(L)||pos<0||pos>(L->last))
	{
		puts("delete failed");
		return -1;
	}
	L->data[pos]=x;
	return 1;
}

int search_seqlist(seqlist *L, data_t x)
{
	if(L==NULL)
	{
		puts("seqlist is NULL");
		return -1;
	}
	if(is_empty_seqlist(L))
	{
		puts("delete failed");
		return -1;
	}
	for(int i=0;i<=L->last;i++)
	{
		if(L->data[i] == x)
			return i;
	}
	return -1;
}

