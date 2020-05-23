#include "btree.h"
#include "queue.h"


btree_pnode create_btree(void)
{
	data_t d;
	printf("input btree:");
	scanf("%c",&d);
	while(getchar() != '\n');
	if('#' == d)
	{
		return NULL;
	}
	else{
		btree_pnode t;
		if((t=(btree_pnode)malloc(sizeof(btree_node))) == NULL)
		{
			puts("malloc failed");
			exit(0);
		}
		t->data=d;
		t->lchild=create_btree();
		t->rchild=create_btree();
		return t;
	}
}

void pre_btree(btree_pnode BT)
{
	if(BT == NULL)
	{
		return;
	}
	printf("%c",BT->data);
	pre_btree(BT->lchild);
	pre_btree(BT->rchild);
}

void mid_btree(btree_pnode BT)
{
	if(BT == NULL)
	{
		return;
	}
	mid_btree(BT->lchild);
	printf("%c",BT->data);
	mid_btree(BT->rchild);
}

void aft_btree(btree_pnode BT)
{
	if(BT == NULL)
	{
		return;
	}
	aft_btree(BT->lchild);
	aft_btree(BT->rchild);
	printf("%c",BT->data);
}


void level_btree(btree_pnode BT)
{
	que_pnode queue;
	btree_pnode temp;
	temp=BT;
	queue=create_queue();
	while(temp != NULL){
		if(temp!=NULL)
		{
			printf("%c",temp->data);
		}
		if(temp->lchild!=NULL)
		{
			in_queue(queue, temp->lchild);
		}
		if(temp->rchild!=NULL)
		{
			in_queue(queue, temp->rchild);
		}
		if(!is_empty_queue(queue))
		{
			temp=out_queue(queue);
		}
		else
		{
			break;
		}
	}
}
