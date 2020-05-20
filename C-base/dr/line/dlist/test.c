#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"

int main(int argc, char *argv[])
{
	dlinklist H;
	H=create_dlist();
	for(int i=0;i<5;i++)
	{
		int num;
		printf("input a num:");
		scanf("%d",&num);
		insert_dlist(H, num, 0);
	}
	show_dlist(H);

	puts("=================");
	for(int i=0;i<5;i++)
	{
		int num;
		dlinklist temp;
		printf("input a num:");
		scanf("%d",&num);
		temp=get_dlist(H, num);
		if(temp != NULL)
			printf("get_data=%d\n",temp->data);
		delete_dlist(H, num);
		show_dlist(H);
	}
	puts("=================");


	show_dlist(H);
	return 0;
}
