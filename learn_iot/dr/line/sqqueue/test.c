#include "sqqueue.h"

int main(int argc, char *argv[])
{
	queuelink q;
	q=create_queue();
	for(int i=0;i<6;i++)
	{
		data_t num;
		scanf("%d",&num);
		in_queue(q, num);
		show_queue(q);
	}
	for(int i=0;i<5;i++)
	{
		printf("data=%d\n",out_queue(q));
		show_queue(q);
	}

	clear_queue(q);
}
