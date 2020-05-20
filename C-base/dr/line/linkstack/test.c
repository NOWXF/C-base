#include "linkstack.h"

int main(int argc, char * argv[])
{
	linkstack s;
	s=create_stack();

	for(int i=0;i<5;i++)
	{
		data_t num;
		printf("input:");
		scanf("%d",&num);
		push_stack(s, num);
	}
	printf("top:%d\n",get_top_stack(s));
	for(int i=0;i<5;i++)
	{
		printf("data=%d\n",pop_stack(s));
	}

	printf("empty:%d\n",is_empty_stack(s));
	clear_stack(s);
	return 0;
}
