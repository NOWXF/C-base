#include <stdio.h>
#include <stdlib.h>

void show(int *arr,int size);
void bubble_sort(int *arr, int size);

int main()
{
	int arr[8]={50,36,66,76,95,12,25,36};
	int size=sizeof(arr)/sizeof(int);

	show(arr,size);
	bubble_sort(arr, size);
	show(arr,size);

	return 0;
}

void show(int *arr,int size)
{
	for(int i=0;i<size;i++)
		printf("%d ",arr[i]);
	printf("\n");
}

void bubble_sort(int *arr, int size)
{
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size-i-1;j++)
		{
			if(arr[j] > arr[j+1])
			{
				int temp=arr[j+1];
				arr[j+1]=arr[j];
				arr[j]=temp;
			}
		}
	}
}
