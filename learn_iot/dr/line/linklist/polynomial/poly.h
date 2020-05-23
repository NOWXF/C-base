#ifndef __POLY_H__
#define __POLY_H__

typedef struct{
	int coe;
	int exp;
}data_t;

typedef struct node{
	data_t data;
	struct node *next;
}polynode,*polylink;

extern polylink create_poly(void);
extern void clear_poly(polylink H);
extern void show_poly(polylink H);

extern int insert_poly(polylink H, data_t x);
extern polylink merge_poly(polylink A, polylink B);

#endif
