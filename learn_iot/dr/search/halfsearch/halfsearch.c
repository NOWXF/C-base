#include <stdio.h>
#include <stdlib.h>

#define N 10

int halfsearch(int *arr, int key);
void up_order(int *arr);

int main(int argc,const char *argv[])
{
	int a[N]={ 43, 21, 34, 13, 45, 12, 54, 23, 90, 33};
	int pos,key;
	char ch;

	up_order(a);
	for(int i=0;i<N;i++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
	while(1)
	{
		printf("input a key:");
		scanf("%d",&key);
		pos = halfsearch(a, key);
		if(-1 == pos)
			printf("search failed!\n");
		else
			printf("serach %d at %d\n",key , pos);
		while(getchar() != '\n');
		printf("continue?(y|Y)");
		scanf("%c",&ch);
		if('y' == ch || 'Y' == ch)
			continue;
		else
			break;
	}

	return 0;
}

//将数组进行升序排列
void up_order(int *arr)
{
	for(int i=0;i<N;i++)
		for(int j=0;j<N-i-1;j++)
		{
			if(arr[j] > arr[j+1])
			{
				int temp=arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
}

//折半查找
int halfsearch(int *arr, int key)
{
	int mid,start,end;
	start=0;
	end=N-1;
	mid=(start+end)/2;
	while(start < end)
	{
		if(arr[mid] > key)
		{
			end=mid-1;
			mid=(start+end)/2;
		}
		if(arr[mid] < key)
		{
			start=mid+1;
			mid=(start+end)/2;
		}
		if(arr[mid] == key)
			break;
	}
	if(arr[mid] == key)
		return mid;
	else
		return -1;
}
