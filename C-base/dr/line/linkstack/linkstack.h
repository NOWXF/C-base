#ifndef __LINKSTACK_H__
#define __LINKSTACK_H__

#include <stdio.h>
#include <stdlib.h>

typedef int data_t;

typedef struct node{
	data_t data;
	struct node *next;
}stacknode,*linkstack;

extern linkstack create_stack(void);
extern void clear_stack(linkstack s);
extern int is_empty_stack(linkstack s);
extern int is_full_stack(linkstack s);
extern int push_stack(linkstack s, data_t value);
extern data_t pop_stack(linkstack s);
extern data_t get_top_stack(linkstack s); 

#endif
