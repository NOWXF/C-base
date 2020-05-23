#include <stdio.h>
#include <string.h>

#define N 20

struct student{
	int no;
	char name[N];
	float score;
}s3,s4;

int main()
{
	struct student s1,s2;
	s1.no = 1;
	strcpy(s1.name,"s1");
	s1.score = 99;

	printf("%d %s %.2f\n",s1.no,s1.name,s1.score);

	s2 = s1;
	s2.no = 2;
	printf("%d %s %.2f\n",s2.no,s2.name,s2.score);

	return 0;
}
