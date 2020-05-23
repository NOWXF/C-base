#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20
typedef struct student{
	int no;
	char name[N];
	float score;
}Stu;

Stu * stu_info()
{
	Stu * p;
	if((p=(Stu *)malloc(sizeof(Stu))) == NULL){
		printf("malloc failed!\n");
		return NULL;
	}
	p->no = 1;
	strcpy(p->name, "s1");
	p->score = 90;

	return p;
}

int main()
{
	Stu *s;
	s=stu_info();

	if(s == NULL)
		return 0;
	printf("Stu info:%d %s %.2f\n",s->no, s->name, s->score);

	free(s);

	return 0;
}
