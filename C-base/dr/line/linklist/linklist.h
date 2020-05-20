#ifndef __LINKLIST_H__
#define __LINKLIST_H__

typedef int data_t;

typedef struct node{
	data_t data;
	struct node *next;
}listnode,*linklist;

extern linklist creat_linklist(void);
extern linklist creat1_linklist(void);
extern void clear_linklist(linklist L);
extern void show_linklist(linklist L);

extern int insert_linklist(linklist L, data_t x, int pos);
extern int order_insert_linklist(linklist L, data_t x);
extern linklist get_by_pos_linklist(linklist L, int pos);
extern linklist get_by_data_linklist(linklist L, data_t x);
extern int delete_by_pos_linklist(linklist L, int pos);
extern int delete_by_data_linklist(linklist L, data_t x);
extern linklist reverse_linklist(linklist L);
extern void self_reverse_linklist(linklist L);
extern void sort_linklist(linklist L);
extern void join_linklist(linklist L, linklist K);

#endif
