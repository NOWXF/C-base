#include "btree.h"
#include "queue.h"
#include "stack.h"


btree_pnode create_btree(void)
{
	data_t d;
	//printf("input btree:");
	scanf("%c",&d);
	//while(getchar() != '\n');
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

void unpre_btree(btree_pnode BT)
{
	stack_pnode stack;
	create_stack(&stack);
	while(BT != NULL || !is_empty_stack(stack))
	{
		if(BT != NULL)
		{
			printf("%c",BT->data);
			if(BT->rchild != NULL)
				push_stack(stack, BT->rchild);
			BT=BT->lchild;
		}
		else{
			BT=pop_stack(stack);
		}
	}
	/*
	while(BT != NULL)
	{
		printf("%c",BT->data);
		if(BT->rchild != NULL)
		{
			push_stack(stack, BT->rchild);
		}
		if(BT->lchild != NULL)
		{
			BT=BT->lchild;
		}
		else{
			if(!is_empty_stack(stack))
				BT=pop_stack(stack);
			else
				break;
		}	
	}
	*/
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

void unmid_btree(btree_pnode BT)
{
	stack_pnode stack;
	create_stack(&stack);
	while(BT != NULL || !is_empty_stack(stack))
	{
		if(BT != NULL)
		{
			push_stack(stack, BT);
			BT=BT->lchild;
		}
		else{
			BT=pop_stack(stack);
			printf("%c",BT->data);
			BT=BT->rchild;
		}
	}
	/*
	while(BT != NULL)
	{
		if(BT->lchild != NULL)
		{
			push_stack(stack, BT);
			BT=BT->lchild;
			continue;
		}
		else{
			printf("%c",BT->data);
			if(BT->rchild != NULL)
			{
				BT=BT->rchild;
				continue;
			}
			else{
				do{
					BT=pop_stack(stack);
					printf("%c",BT->data);
				}while(BT->rchild==NULL && !is_empty_stack(stack));
				if(BT->rchild != NULL)
				{
					BT=BT->rchild;
					continue;
				}
			}
		}
		if(is_empty_stack(stack))
			break;
	}
	*/
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

void unaft_btree(btree_pnode BT)
{
	stack_pnode stack;
	btree_pnode pass=NULL;
	create_stack(&stack);
	push_stack(stack, BT);
	while(!is_empty_stack(stack))
	{
		BT=get_top_stack(stack);
		if((NULL == BT->lchild && NULL == BT->rchild) || (NULL != pass && (pass == BT->rchild || pass == BT->lchild)))
		{
			printf("%c",BT->data);
			pass = BT;
			pop_stack(stack);
		}
		else{
			if(NULL != BT->rchild)
			{
				push_stack(stack, BT->rchild);
			}
			if(NULL != BT->lchild)
			{
				push_stack(stack, BT->lchild);
			}
		}
	}
	free(stack);
	stack=NULL;
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

//回调函数：使用函数指针来调用同一类型函数
//pfun=函数地址（函数名称)
void travel(char const *str,void (*pfun)(btree_pnode),btree_pnode t)
{
	printf("%s",str);
	pfun(t);
	printf("\n");
}
