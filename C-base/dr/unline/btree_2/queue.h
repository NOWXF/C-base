#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

typedef btree_pnode que_t;
typedef struct queue{
	que_t data;
	struct queue *next;
}queue_node,* queue_pnode;

typedef struct{
	queue_pnode front,rear;
}que_node,*que_pnode;

extern que_pnode create_queue(void);
extern int is_empty_queue(que_pnode q);
extern int in_queue(que_pnode q, que_t value);
extern que_t out_queue(que_pnode q);

#endif
