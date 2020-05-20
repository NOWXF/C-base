#include <stdio.h>
#include <string.h>

#define N 20

struct student{
	int no;
	char name[N];
	struct{
		int year;
		int month;
		int day;
	}date;
	float score;
}s1={1, "s1", {1998, 10, 1}, 99};

int main()
{
	struct student s2;
	s2.no = 2;
	strcpy(s2.name, "s2");
	s2.date.year = 2020;
	s2.date.month = 12;
	s2.date.day = 2;
	s2.score = 90;

	printf("size:%d\n",sizeof(s1));
	printf("%d %s %d-%d-%d %.2f\n",s1.no, s1.name, s1.date.year, s1.date.month, s1.date.day, s1.score);

	printf("%d %s %d-%d-%d %.2f\n",s2.no, s2.name, s2.date.year, s2.date.month, s2.date.day, s2.score);

	return 0;
}
