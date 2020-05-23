#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

typedef btree_pnode stack_t;
typedef struct s_node{
	stack_t data;
	struct s_node *next;
}stack_node,*stack_pnode;

extern void create_stack(stack_pnode *s);
extern int is_empty_stack(stack_pnode s);
extern int push_stack(stack_pnode s, stack_t value);
extern stack_t pop_stack(stack_pnode s);
extern stack_t get_top_stack(stack_pnode s);

#endif
