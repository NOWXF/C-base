#ifndef __JOSEPH_H__
#define __JOSEPH_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node *next;
}josenode,*joselink;

extern joselink create_jose(void);
extern void show_jose(joselink H);

extern void out_jose(joselink H, int k, int m);

#endif
