#include <stdio.h>

#define N 20
struct student
{
	int no;
	char name[N];
	float score;
}s2[2];

int main()
{
	struct student s1[3]={{1, "s1", 99},{2, "s2", 90},{3, "s3", 89}};

	s2[0]=s1[0];
	s2[1]=s1[1];

	for(int i=0;i<sizeof(s1)/sizeof(struct student);i++)
	{
		printf("s1:%d-%s-%f\n",s1[i].no, s1[i].name, s1[i].score);
	}
	return 0;
}
