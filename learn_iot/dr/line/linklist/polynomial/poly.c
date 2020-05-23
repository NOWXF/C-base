#include <stdio.h>
#include <stdlib.h>
#include "poly.h"


polylink create_poly(void)
{
	polylink H;
	if((H=(polylink)malloc(sizeof(polynode))) == NULL)
	{
		puts("malloc failed");
		return NULL;
	}
	H->next=NULL;
	return H;
}

void clear_poly(polylink H)
{
	polylink temp;
	temp=H;
	while(temp)
	{
		H=H->next;
		free(temp);
		temp=NULL;
		temp=H;
	}
}

void show_poly(polylink H)
{
	H=H->next;
	while(H)
	{
		printf("(%d)X^%d+",H->data.coe, H->data.exp);
		H=H->next;
	}
	puts("");
}


int insert_poly(polylink H, data_t x)
{
	polylink d,r;
	if((d=(polylink)malloc(sizeof(polynode))) == NULL)
	{
		puts("malloc failed");
		return -1;
	}
	d->data=x;
	r=H;
	while(r->next != NULL)
	{
		r=r->next;
	}
	r->next=d;
	d->next=NULL;
	return 1;
}

polylink merge_poly(polylink A, polylink B)
{
	polylink pa,pb,C;
	if((C=(polylink)malloc(sizeof(polynode))) == NULL)
	{
		puts("malloc failed");
		return NULL;
	}
	C->next=NULL;
	pa=A->next;
	pb=B->next;
	while(pa != NULL && pb != NULL)
	{
		data_t *temp;
		if((temp=(data_t  *)malloc(sizeof(data_t))) == NULL)
		{
			puts("malloc failed");
			return NULL;
		}
		if(pa->data.exp == pb->data.exp)
		{
			temp->coe=pa->data.coe+pb->data.coe;
			temp->exp=pa->data.exp;
			if(temp->coe == 0)
			{
				free(temp);
				temp=NULL;
				pa=pa->next;
				pb=pb->next;
				continue;
			}	
			pa=pa->next;
			pb=pb->next;
		}
		else if(pa->data.exp < pb->data.exp)
		{
			*temp=pa->data;	
			pa=pa->next;
		}else{
			*temp=pb->data;
			pb=pb->next;
		}
		insert_poly(C, (*temp));	
	}
	if(pa == NULL)
	{
		while(pb != NULL)
		{
			insert_poly(C, pb->data);
			pb=pb->next;
		}
	}
	if(pb == NULL)
	{
		while(pa != NULL)
		{
			insert_poly(C, pa->data);
			pa=pa->next;
		}
	}
	return C;
}
