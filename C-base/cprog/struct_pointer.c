#include <stdio.h>

#define N 20
struct student
{
	int no;
	char name[N];
	float score;
};

void show_struct(struct student *p, int n)
{
	for(int i=0;i<n;i++)
	{
		printf("%d-%s-%f\n",p->no, p->name, p->score);
		p++;
	}
}

int main()
{
	struct student s1[3]={{1, "s1", 99},{2, "s2", 90},{3, "s3", 89}};

	show_struct(s1, sizeof(s1)/sizeof(struct student));
	return 0;
}
