#ifndef __SQSTACK_H__
#define __SQSTACK_H__

#include <stdio.h>
#include <stdlib.h>

typedef int data_t;
typedef struct{
	data_t *data;
	int maxlen;
	int top;
}sqstack;

extern sqstack * create_stack(int len);
extern void clear_stack(sqstack *s);
extern int is_empty_stack(sqstack *s);
extern int is_full_stack(sqstack *s);
extern int push_stack(sqstack *s, data_t x);
extern data_t pop_stack(sqstack *s);
extern data_t get_top_stack(sqstack *s);
extern void free_stack(sqstack *s);

#endif
