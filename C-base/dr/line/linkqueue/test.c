#include "linkqueue.h"

int main()
{
	queuelink QL;
	QL = create_queue();
	while(1)
	{
		data_t num;
		printf("input:");
		if(1 == scanf("%d",&num))
		{
			if(-1 == num)
				break;
			in_queue(QL, num);
			show_queue(QL);
		}
		else
		{
			printf("out:%d\n",out_queue(QL));
			show_queue(QL);
			while(getchar() != '\n');
		}

	}
	clear_queue(QL);
	return 0;
}
