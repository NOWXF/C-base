#include "joseph.h"

joselink create_jose(void)
{
	joselink H,r;
	int num=0;
	printf("input count:");
	scanf("%d",&num);
	if(num <= 0)
	{
		puts("count too small");
		return NULL;
	}else{
		if((H=(joselink)malloc(sizeof(josenode))) == NULL)
		{
			puts("malloc failed");
			return NULL;
		}
		H->data=1;
		H->next=H;
		r=H;
		for(int i=2;i<=num;i++)
		{
			joselink temp;
			if((temp=(joselink)malloc(sizeof(josenode))) == NULL)
			{
				puts("malloc failed");
				return NULL;
			}
			temp->data=i;
			temp->next=r->next;
			r->next=temp;
			r=r->next;
		}
	}
	return H;
}

void show_jose(joselink H)
{
	joselink p;
	p=H;
	printf("data=");
	do{
		printf("%d  ",p->data);
		p=p->next;
	}while(p != H);
	puts("");
}

void out_jose(joselink H, int k, int m)
{
	joselink r=H,temp;
	while(--k)
	{
		temp=r;
		r=r->next;
	} 
	printf("out=");
	while(r->next != r){
		for(int i=1;i<m;i++)
		{
			temp=r;
			r=r->next;
		}
		temp->next=r->next;
		printf("%d  ",r->data);
		free(r);
		r=NULL;
		r=temp->next;
	}
	printf("%d\n",r->data);
	free(r);
	r=NULL;
}
