#ifndef __SQQUEUE_H__
#define __SQQUEUE_H__

#include <stdio.h>
#include <stdlib.h>

typedef int data_t;
#define MAXSIZE 5

typedef struct node{
	data_t data[MAXSIZE];
	int front,rear;
}queuenode,*queuelink;

extern queuelink create_queue();
extern void clear_queue(queuelink Q);
extern void show_queue(queuelink Q);
extern int is_empty_queue(queuelink Q);
extern int is_full_queue(queuelink Q);
extern int in_queue(queuelink Q, data_t value);
extern data_t out_queue(queuelink Q);

#endif
