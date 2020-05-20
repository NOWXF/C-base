#ifndef __LINKQUEUE_H__
#define __LINKQUEUE_H__

#include <stdio.h>
#include <stdlib.h>

typedef int data_t;
typedef struct node{
	data_t data;
	struct node *next;
}linkqueue_node,*linkqueue_p;
typedef struct{
	linkqueue_p front,rear;
}queuenode,*queuelink;

extern queuelink create_queue(void);
extern void clear_queue(queuelink Q);
extern void show_queue(queuelink Q);
extern int is_empty_queue(queuelink Q);
extern int in_queue(queuelink Q, data_t value);
extern data_t out_queue(queuelink Q);

#endif
