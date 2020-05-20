#ifndef __BTREE_H_
#define __BTREE_H_

#include <stdio.h>
#include <stdlib.h>

typedef char data_t;
typedef struct node{
	data_t data;
	struct ndoe *lchild,*rchild;
}btree_node,*btree_pnode;

extern btree_pnode create_btree(void);
extern void pre_btree(btree_pnode BT);
extern void mid_btree(btree_pnode BT);
extern void aft_btree(btree_pnode BT);
extern void level_btree(btree_pnode BT);

#endif
