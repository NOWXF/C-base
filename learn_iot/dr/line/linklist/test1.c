#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

int main(int argc, const char *argv[])
{
	linklist L;
	L = creat1_linklist();
#if 0
	L = creat_linklist();
	for(int i=0;i<3;i++)
	{
		int num;
		scanf("%d",&num);
		insert_linklist(L, num, i+1);
	}
#endif
	show_linklist(L);
	puts("========================");
	
#if 0
	for(int i=0;i<3;i++)
	{
		int num;
		linklist p=NULL;
		scanf("%d",&num);
		p=get_by_data_linklist(L, num);
		if(p == NULL)
			puts("NULL");
		else
			printf("get_data:%d\n",p->data);
	}
#endif

#if 0
	linklist r = reverse_linklist(L);
	show_linklist(r);

	for(int i=0;i<3;i++)
	{
		int num;
		printf("input del num:");
		scanf("%d",&num);
		delete_by_data_linklist(L, num);
		show_linklist(L);
	}
#endif
	self_reverse_linklist(L);
	show_linklist(L);
	
	
	clear_linklist(L);
	return 0;
}
