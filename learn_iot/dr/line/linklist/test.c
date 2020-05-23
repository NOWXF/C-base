#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

int main(int argc, const char *argv[])
{
	linklist L,K;
	L = creat1_linklist();
	show_linklist(L);
	K = creat1_linklist();
	show_linklist(K);
	puts("========================");
	sort_linklist(L);
	show_linklist(L);
	puts("========================");
	sort_linklist(K);
	show_linklist(K);
	puts("========================");
	join_linklist(L, K);
	show_linklist(L);
	
#if 0
	int num;
	for(int i=0;i<3;i++)
	{
		printf("input a num:");
		scanf("%d",&num);
		order_insert_linklist(L, num);
		show_linklist(L);
		puts("========================");
	}
#endif
	puts("========================");
	show_linklist(L);
	clear_linklist(L);
	return 0;
}
