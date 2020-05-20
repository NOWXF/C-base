#include <stdio.h>
#include <stdlib.h>

#define N 10
int seqsearch(int *arr,int key);

int main(int argc, const char * argv[])
{
	int a[N]={2, 3, 1, 5, 7, 2, 8, 4, 9, 5};
	int pos,key;
	char ch;

	while(1)
	{
		printf("please input a key:");
		scanf("%d",&key);
		pos=seqsearch(a, key);
		if(-1 == pos)
			printf("search failed\n");
		else
			printf("search %d at %d\n",key, pos);
		printf("continue?(y|Y)");
		while(getchar() != '\n');
		scanf("%c",&ch);
		while(getchar() != '\n');
		if('y' == ch || 'Y' == ch)
			continue;
		else
			break;
	}

	return 0;
}

int seqsearch(int *arr,int key)
{
	int i;
	for(i=N-1;i>=0;i--)
		if(arr[i] == key)
			return i;
	return i;
}
