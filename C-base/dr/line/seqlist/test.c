#include <stdio.h>
#include <stdlib.h>
#include "seqlist.h"

int main(int argc, const char *argv[])
{
	seqlist *L;
	L=creat_seqlist();
	for(int i=0;i<5;i++)
		insert_seqlist(L, i, 0);
	show_seqlist(L);
	puts(" ");

	delete_seqlist(L, 2);
	show_seqlist(L);
	puts(" ");

	change_seqlist(L, 13, 3);
	show_seqlist(L);
	puts(" ");

	int num=0;
	scanf("%d",&num);
	printf("pos=%d\n", search_seqlist(L, num));
	
	while(!is_full_seqlist(L))
	{
		insert_seqlist(L, num, L->last+1);
		printf("length=%d,is_empty=%d,is_full=%d\n",get_length_seqlist(L), is_empty_seqlist(L), is_full_seqlist(L));
	}

	set_empty_seqlist(L);
	printf("length=%d,is_empty=%d,is_full=%d\n",get_length_seqlist(L), is_empty_seqlist(L), is_full_seqlist(L));


	clear_seqlist(L);
	return 0;
}
