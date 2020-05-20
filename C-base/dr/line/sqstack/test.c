#include "sqstack.h"

int main(int argc, char *argv[])
{
	sqstack *s;
	int n=10;
	s=create_stack(n);

#if 0
	push_stack(s, 10);
	push_stack(s, 20);
	push_stack(s, 30);
#endif

	while(!is_full_stack(s))
	{
		data_t d;
		scanf("%d",&d);
		push_stack(s, d);
		printf("is full:%d\n", is_full_stack(s));
	}

	while(!is_empty_stack(s))
	{
		printf("top:%d\n",pop_stack(s));
		printf("is empty:%d\n", is_empty_stack(s));
	}

	free_stack(s);

	return 0;
}
