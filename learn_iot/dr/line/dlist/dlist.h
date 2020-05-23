#ifndef __DLIST_H__
#define __DLIST_H__

typedef int data_t;

typedef struct dlist{
	data_t data;
	struct dlist *prior,*next;
}dlistnode,*dlinklist;

extern dlinklist create_dlist(void);
extern void show_dlist(dlinklist H);

extern int insert_dlist(dlinklist H, data_t x, int pos);
extern dlinklist get_dlist(dlinklist H, int pos);
extern int delete_dlist(dlinklist H, int pos);

#endif
