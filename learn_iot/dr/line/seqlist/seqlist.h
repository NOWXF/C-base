#ifndef __SEQLIST_H__
#define __SEQLIST_H__

#define MAXSIZE 100
typedef int data_t;

typedef struct{
	data_t data[MAXSIZE];
	int last;
}seqlist;

seqlist *creat_seqlist(void);
void clear_seqlist(seqlist *L);

int is_empty_seqlist(seqlist *L);
int is_full_seqlist(seqlist *L);
void set_empty_seqlist(seqlist *L);
int get_length_seqlist(seqlist *L);
void show_seqlist(seqlist *L);

int insert_seqlist(seqlist *L, data_t x, int pos);
int delete_seqlist(seqlist *L, int pos);
int change_seqlist(seqlist *L, data_t x, int pos);
int search_seqlist(seqlist *L, data_t x);

#endif
