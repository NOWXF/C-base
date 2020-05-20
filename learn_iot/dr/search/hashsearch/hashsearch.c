#include <stdio.h>
#include <stdlib.h>

#define N 10

void create_hash_table(int *arr, int *ht, int size);
int hash_search(int *ht,int key);

int main(int argc, const char *argv[])
{
	int arr[N]={56, 23, 89, 45, 23, 67, 12, 78, 85, 90};
	int pos,key;
	char ch;
	int size=N/0.75+0.5;
	int ht[]={0};
	//创建hash表
	//使用线性探查法
	create_hash_table(arr, ht, size);

	for(int i;i<size;i++)
		printf("%d ",ht[i]);
	printf("\n");

	while(1)
	{
		printf("input a key:");
		scanf("%d",&key);
		pos = hash_search(ht,key);
		if(-1 == pos)
		{
			puts("search failed");
		}
		else{
			printf("search %d at %d\n",key, pos);
		}
		printf("continue?(y|Y)");
		while(getchar() != '\n');
		scanf("%c",&ch);
		if('y' == ch || 'Y' == ch)
			continue;
		else
			break;
	}
	return 0;
}


void create_hash_table(int *arr, int *ht, int size)
{
	int temp;
	for(int i=0;i<N;i++)
	{
		temp = arr[i]%7;
		//保留余数法
		if(0 == ht[temp])
			ht[temp]=arr[i];
		else   //出现冲突，使用线性探查法处理
		{
			for(int j=1;j<size-1;j++)
			{
				temp = (temp+j)%size;
				if(0 == ht[temp])
				{
					ht[temp]=arr[i];
					break;
				}
			}
		}
	}
}

int hash_search(int *ht,int key)
{
	int hash;
	hash=key%7;

	while(ht[hash] != 0)
	{
		if(ht[hash] == key)
		{
			return hash;
		}
		hash++;
	}
	return -1;
}
